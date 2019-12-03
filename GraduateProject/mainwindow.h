#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include "maze.h"
#include "solver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_loadFileBtn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_backBtn_clicked();

    void on_resetBtn_clicked();

    void on_nextBtn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::unique_ptr<Maze> maze;
    std::unique_ptr<Solver> solver;
	size_t step = 0;
	std::vector<std::vector<std::optional<Heuristic>>> heuristic;
	std::unique_ptr<step_AStar> step_Astar_ptr;
    void DrawMaze();
};

#endif // MAINWINDOW_H
