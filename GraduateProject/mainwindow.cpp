#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <iostream>
#include <QMessageBox>

using namespace std;

static bool generated=false;

constexpr auto black=qRgb(0,0,0);
constexpr auto white=qRgb(255,255,255);
constexpr auto blue=qRgb(0, 0, 255);
constexpr auto green = qRgb(0, 255, 0);
constexpr auto yellow = qRgb(255, 255, 0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->infoLabel->clear();
    ui->pushButton_2->setEnabled(false);
	ui->backBtn->setEnabled(false);
	ui->nextBtn->setEnabled(false);
	ui->resetBtn->setEnabled(false);

    /*set combo box methods*/
    ui->comboBox->addItem("Breadth First Search");
    ui->comboBox->addItem("Depth First Search");
    ui->comboBox->addItem("A* Search");
    ui->comboBox->addItem("Uniform Cost Search");
	

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()	//generate button pushed
{
    ui->infoLabel->clear();
    maze=make_unique<Maze>(static_cast<size_t>(ui->rowBox->value()),static_cast<size_t>(ui->colBox->value()));
    maze->Generate();
    generated=true;
    /*Debug*/
        //maze->Show();
    scene=new QGraphicsScene(this);
    DrawMaze();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    ui->pushButton_2->setEnabled(true);
	ui->nextBtn->setEnabled(true);
	
	/*reset stepping mode*/
	heuristic.clear();
	step = 0;
	ui->backBtn->setEnabled(false);
}

void MainWindow::DrawMaze()
{
    static QPen blackpen{Qt::black};
    static QPen whitepen{Qt::white};

    QImage maze_img(maze->maze[0].size(), maze->maze.size(), QImage::Format_Mono);
    maze_img.fill(true);
    if(maze)
    {
        for(size_t row=0; row!=maze->maze.size(); ++row)
        {
            for(size_t col=0; col!=maze->maze[0].size(); ++col)
            {
                if(maze->maze[row][col])
                {
                    maze_img.setPixel(col, row, true);
                }
                else
                    maze_img.setPixel(col, row, false);
            }
        }
    }
    scene->addPixmap(QPixmap::fromImage(maze_img));
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!generated)
    {
        QMessageBox::critical(this, "Error", "Maze has not generated!");
        return;
    }
    /*Disable the "Solve" button*/
    ui->pushButton_2->setEnabled(false);
    solver=make_unique<Solver>(maze.get());
    /*Solving*/
    result result;
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        result=solver->BreadthFirstSearch();
        break;
    case 1:
        result=solver->DepthFirstSearch();
        break;
    case 2:
        result=solver->AStarSearch();
        break;
    case 3:
        result=solver->UniformSearch();	//!
		break;
    }
    /*Print result*/
//    for(auto& path:result.path)
//        cout<<"("<<path.first<<","<<path.second<<")\n";
    /*Debug*/
        //cout << "Total expansion=" << result.expansion;
	if (result.path.empty())
		ui->infoLabel->setText(QString("No solution!") += QString("\t Time") += (QString::number((double)result.duration.count() / 1000.0)) += QString("sec"));
	else
		ui->infoLabel->setText(QString("Total expansion=")+=(QString::number(result.expansion)+=QString("\t Time=")+=(QString::number((double)result.duration.count()/1000.0)))+=QString("sec"));

    /*Draw solution*/
    QImage solution_img(maze->cols, maze->rows, QImage::Format::Format_RGB888);
    for(size_t row=0; row!=maze->maze.size(); ++row)
    {
        for(size_t col=0; col!=maze->maze[0].size(); ++col)
        {
            if(maze->maze[row][col])
            {
                solution_img.setPixel(col, row, white);

            }
            else
                solution_img.setPixel(col, row, black);
            //if(solver->getNodes()[row][col].has_value())
            //    solution_img.setPixel(col, row, blue);
        }
    }

    for(auto& pixel:result.path)
    {
        solution_img.setPixel(pixel.second, pixel.first, qRgb(255,0,0));
    }
    scene->addPixmap(QPixmap::fromImage(solution_img));
}

void MainWindow::on_loadFileBtn_clicked()
{

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->pushButton_2->setEnabled(true);
}
void MainWindow::on_backBtn_clicked()
{
	if (--step)
		ui->backBtn->setEnabled(false);
}

void MainWindow::on_resetBtn_clicked()
{
    QImage maze_img(maze->maze[0].size(), maze->maze.size(), QImage::Format::Format_RGB888);
    maze_img.fill(true);
    if(maze)
    {
        for(size_t row=0; row!=maze->maze.size(); ++row)
        {
            for(size_t col=0; col!=maze->maze[0].size(); ++col)
            {
                if(maze->maze[row][col])
                {
                    maze_img.setPixel(col, row, white);
                }
                else
                    maze_img.setPixel(col, row, black);
                if(solver->getNodes()[row][col].has_value())
                    maze_img.setPixel(col, row, blue);
            }
        }
    }
    scene->addPixmap(QPixmap::fromImage(maze_img));
    ui->pushButton_2->setEnabled(true);
	ui->backBtn->setEnabled(false);
	solver.reset();
	step = 0;
}

void MainWindow::on_nextBtn_clicked()
{
	if (maze)
	{
		if(!solver)
			solver = make_unique<Solver>(maze.get());
		QImage img(maze->cols, maze->rows, QImage::Format::Format_RGB888);
		img.fill(true);
		switch (ui->comboBox->currentIndex())
		{
		case 0:
			//result = solver->BreadthFirstSearch();
			break;
		case 1:
			//result = solver->DepthFirstSearch();
			break;
		case 2:
		{
			++step;
			if (heuristic.empty())
			{
				step_Astar_ptr = make_unique<step_AStar>();
				if (!solver->nodesMade)
				{
	
					solver->makeNodes();
				}
				heuristic = makeNodesWithHeuristic(solver->getNodes());				
				step_Astar_ptr->visited.resize(maze->rows);
				for (auto& each_row : step_Astar_ptr->visited)
				{
					each_row.resize(maze->cols, false);
				}
			}
			int step_count = ui->spinBox_3->value();
			while (step_count--)
			{
				if (solver->AStarSearch_Step(*step_Astar_ptr, heuristic))	//solution find£¡
				{
					QMessageBox::warning(this, "Solution Find!", "The solution is found!");
					return;
				}
				priority_queue temp = step_Astar_ptr->fringe;
				while (!temp.empty())
				{
					img.setPixel(temp.top()._position.second, temp.top()._position.first, green);
					temp.pop();
				}
			}
			break;
		}
		case 3:
			//result = solver->UniformSearch();
			break;
		}
		scene->addPixmap(QPixmap::fromImage(img));
		++step;
		ui->backBtn->setEnabled(true);
		ui->resetBtn->setEnabled(true);
	}
	else
	{
		QMessageBox::critical(this, "Error", "Maze has not generated!");
	}
}
