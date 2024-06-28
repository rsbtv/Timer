#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer> // подключение библиотеки
#include <QTime>
#include <QFont>
#include <QStringList>
#include <QMessageBox>


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
    void timer_tick(void); // обработчик таймера

    void down_timer_tick(void); // обработчик таймера обратного отсчета

    void wait_timer_tick(void); // обработчик таймера перед нажатием старта

    void start_timer_tick(void); // обработчик старта таймера

    void lap_timer_tick(void); // обработчик таймера для кругов

    int maxLap(int mas_table[], int rows); // поиск максимального времени

    int minLap(int mas_table[], int rows); // поиск минимального времени

    void on_pushButton_Start_clicked(); // кнопка старт

    void on_pushButton_Stop_clicked(); // кнопка стоп

    void on_pushButton_Pause_clicked(); // кнопка паузы

    void on_pushButton_DownCounter_clicked(); // кнопка обратного отсчета

    void on_spinBox_Arm_valueChanged(int sec); // изменение таймера обратного отсчета от спин бокса

    void on_pushButton_Auto_clicked(); // режим автоматического ожидания и старта

//    void on_pushButton_Start_2_clicked(); // кнопка старта третьего таймера

//    void on_pushButton_Stop_2_clicked(); // кнопка стоп третьего таймера

//    void on_pushButton_Pause_2_clicked(); // кнопка паузы третьего таймера

    void on_pushButton_Lap_clicked(); // кнопка сделать круг

    void on_pushButton_Reset_clicked(); // кнопка сброса

    void on_spinBox_Wait_valueChanged(int sec);

//    void on_spinBox_Start_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QTimer * timer; // указатель на таймер
    int counter; // счетчик

    QTimer * down_timer; // указатель на таймер обратного отсчета
    int down_counter;

    QTimer * wait_timer; // таймер ожидает кол-во секунд со спинбокса
    int wait_counter;

    QTimer * start_timer; // таймер стартует после ожидания
    int start_counter;

    QTimer * lap_timer; // таймер для кругов
    int lap_counter;

    int rows;
    int lap;
    int * mas_table; //указатель на одномерный массив
    QString gl_str;
};

#endif // MAINWINDOW_H
