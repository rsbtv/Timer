#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : // конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this); // создали таймер
    counter = 0; // инициализация счетчика
    timer->setInterval(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_tick())); // соединили сигнал таймера с обработчиком

    down_timer = new QTimer(this); // создали таймер
    down_counter = 60; // инициализация счетчика
    down_timer->setInterval(1000);

    connect(down_timer, SIGNAL(timeout()), this, SLOT(down_timer_tick())); // соединили сигнал таймера с обработчиком

    wait_timer = new QTimer(this);
    wait_counter = 0;
    wait_timer->setInterval(1000);

    connect(wait_timer, SIGNAL(timeout()), this, SLOT(wait_timer_tick()));

    start_timer = new QTimer(this);
    start_counter = 0;
    start_timer->setInterval(100);

    connect(start_timer, SIGNAL(timeout()), this, SLOT(start_timer_tick()));

    lap_timer = new QTimer(this); // создали таймер
    lap_counter = 0; // инициализация счетчика

    connect(lap_timer, SIGNAL(timeout()), this, SLOT(lap_timer_tick())); // соединили сигнал таймера с обработчиком
    rows = 0;
    gl_str.clear();

    ui->label->hide();

    ui->lcdNumber->display("00:00:00.00");
    ui->lcdNumber_DownCounter->display("00:01.00");
    ui->lcdNumber_Wait->display("00:00:05");

    this->setWindowTitle("Таймер");

//    ui->pushButton_Start_2->setEnabled(false);
//    ui->pushButton_Pause_2->setEnabled(false);
//    ui->pushButton_Stop_2->setEnabled(false);
    ui->pushButton_Pause->setEnabled(false);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Lap->setEnabled(false);
    ui->pushButton_Reset->setEnabled(false);
    ui->tableWidget->setEnabled(false);

    QStringList str_list;
    str_list.append("Время");
    ui->tableWidget->setColumnWidth(0,320);
    ui->tableWidget->setHorizontalHeaderLabels(str_list);

    mas_table = nullptr;
    mas_table = new int[rows];

}

MainWindow::~MainWindow() // деструктор
{
    delete ui;
}


void MainWindow::timer_tick() // то, что будет вызываться по таймеру
{
    counter++;

    QString str;
    int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд

    str.clear();

    s_sec = counter % 100;
    sec = counter/100;
    m = sec/60;
    sec = sec % 60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));
    str.append(".");

    if (s_sec < 10)
        str.append("0");
    str.append(QString::number(s_sec));

    ui->lcdNumber->display(str);
    ui->tableWidget->setEnabled(false);
//    ui->label_tick->setNum(counter);

//    if (ui->tableWidget->item(rows,0) == nullptr)
//        ui->pushButton_Reset->setEnabled(false);
//    else
//        ui->pushButton_Reset->setEnabled(true);
//    gl_str = str;
}

void MainWindow::down_timer_tick() // то, что будет вызываться по таймеру обратного отсчета
{
    down_counter--;
    ui->spinBox_Arm->setEnabled(false);

    QString str;
    int h, m, sec; // часы, минуты, секунды

    str.clear();

    sec = down_counter%60;

    m = down_counter/60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));

    ui->lcdNumber_DownCounter->display(str);

    if (down_counter == 0)
    {
        ui->label->show();
        down_timer->stop();
        ui->pushButton_Stop->click();
        ui->pushButton_Stop->setEnabled(false);
        ui->pushButton_Pause->setEnabled(false);
        ui->pushButton_Start->setEnabled(false);
        ui->spinBox_Arm->setEnabled(false);
        ui->spinBox_Start->setEnabled(false);
        ui->spinBox_Wait->setEnabled(false);
        ui->pushButton_Auto->setEnabled(false);
        ui->pushButton_Reset->setEnabled(false);
        ui->tableWidget->setEnabled(false);
        wait_timer->stop();
        start_timer->stop();
   }
}

void MainWindow::wait_timer_tick() // то что вызывается по таймеру первого спинбокса
{
//    int sec = wait_counter;
    wait_counter--;

    QString str;
    int h, m, sec, s_sec; // часы, минуты, секунды

    str.clear();

    sec = wait_counter;
    s_sec = wait_counter / 100;
    m = sec/60;
    sec = sec % 60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));
//    str.append(".");

//    if (s_sec < 10)
//        str.append("0");
//    str.append(QString::number(s_sec));

    ui->lcdNumber_Wait->display(str);

    if (wait_counter == 0)
    {
        wait_timer->stop();
//        timer->setInterval(0);
//        start_timer->setInterval(200);
//        timer->start(10);
//        timer->start(10);
        on_pushButton_Start_clicked();
        on_pushButton_Start_clicked();
        start_timer->start(10);
        ui->pushButton_Lap->setEnabled(true);
        ui->pushButton_Pause->setEnabled(true);
        ui->pushButton_Stop->setEnabled(true);

//        on_pushButton_Start_clicked();
    }
}

void MainWindow::start_timer_tick() // то что будет вызываться по таймеру второго спинбокса
{
    start_counter++;

    QString str;
    int h, m, sec; // часы, минуты, секунды, сотые секунд
    int stop = ui->spinBox_Start->value();

    str.clear();

    //s_sec = start_counter % 100;
    sec = start_counter/100;
    m = sec/60;
    sec = sec % 60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));
//    str.append(".");

//    if (s_sec < 10)
//        str.append("0");
//    str.append(QString::number(s_sec));

    ui->lcdNumber_Wait->display(str);
//    ui->label_tick2->setNum(start_counter);

    if (start_counter == stop * 100)
    {
        on_pushButton_Stop_clicked();
        start_timer->stop();
        ui->spinBox_Wait->setEnabled(true);
        ui->spinBox_Start->setEnabled(true);
        ui->pushButton_Auto->setEnabled(true);
//        timer->stop();

    }
}

void MainWindow::lap_timer_tick() // то, что будет вызываться по таймеру
{
    lap_counter++;

    QString str;
    int h, m, sec, s_sec; // часы, минуты, секунды, сотые секунд

    str.clear();

    s_sec = lap_counter % 100;
    sec = lap_counter/100;
    m = sec/60;
    sec = sec % 60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));
    str.append(".");

    if (s_sec < 10)
        str.append("0");
    str.append(QString::number(s_sec));

    gl_str = str;
    lap = lap_counter;

}

int MainWindow::maxLap(int mas_table[], int rows) // поиск максимального времени
{
    int max = mas_table[0]; // минимальное число
    int k = 0;      // индекс минимального элемента

    for (int i = 0; i <= rows; i++) // n - размерность массива
    {
        if (max < mas_table[i])
        {
            max = mas_table[i];
            k = i;
        }
    }
    return k;
}

int MainWindow::minLap(int mas_table[], int rows) // поиск минимального времени
{
    int min = mas_table[0]; // минимальное число
    int k = 0;      // индекс минимального элемента

    for (int i = 0; i <= rows; i++) // n - размерность массива
    {
        if (min > mas_table[i])
        {
            min = mas_table[i];
            k = i;
        }
    }
    return k;
}

void MainWindow::on_pushButton_Start_clicked() // кнопка старт
{
    counter = 0;
    lap_counter = 0;
    timer->start(10); // 10 msec (0.01 sec)
    lap_timer->start(10);
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButton_Pause->setEnabled(true);
    ui->pushButton_Lap->setEnabled(true);
}

void MainWindow::on_pushButton_Stop_clicked() // кнопка стоп
{

    timer->stop();
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Pause->setEnabled(false);
    ui->pushButton_Lap->setEnabled(false);
//    ui->spinBox_Wait->setEnabled(true);
//    ui->spinBox_Start->setEnabled(true);
//    ui->pushButton_Auto->setEnabled(true);
}

void MainWindow::on_pushButton_Pause_clicked() // кнопка паузы
{
    if (timer->isActive())
    {
        timer->stop();
        ui->pushButton_Lap->setEnabled(false);
        ui->pushButton_Pause->setText("Продолжить");
    }
    else
    {
        timer->start(10);
        ui->pushButton_Pause->setText("Пауза");
        ui->pushButton_Lap->setEnabled(true);
    }
}

void MainWindow::on_pushButton_DownCounter_clicked() // запуск обратного таймера
{
    ui->pushButton_DownCounter->setEnabled(false);
    down_counter = ui->spinBox_Arm->value();
    if (down_counter > 0)
        down_timer->start();
    else if (down_counter == 0)
        QMessageBox::information(this, "Ошибка", "Неверное значение", QMessageBox::Ok);

}


// третий таймер и 2 спинбокса по вызову этого таймера
// программа ждет кол-во секунд указанное в первом спинбоксе и нажимает на кнопку старт
// далее ждет кол-во секунд указанное во втором спинбоксе и нажимает кнопку стоп
// при этом можно нажимать кнопки старт стоп пауза независимо а срабатывание таймера армагедона также должно останавливать все

void MainWindow::on_spinBox_Arm_valueChanged(int sec) // вывод обратного отсчета реагирует на изменения в SpinBox`e
{
    down_counter = sec;

    QString str;
    int h, m; // часы, минуты, секунды

    str.clear();


    sec = down_counter%60;

    m = down_counter/60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));

    ui->lcdNumber_DownCounter->display(str);

}

void MainWindow::on_pushButton_Auto_clicked() // режим автоотсчета
{

    wait_counter = 0;
    start_counter = 0;
    counter = 0;
    ui->lcdNumber->display("00:00:00.00");
    wait_counter = ui->spinBox_Wait->value();
    if (wait_counter > 0 or start_counter > 0)
    {
        wait_timer->start();
        ui->spinBox_Wait->setEnabled(false);
        ui->spinBox_Start->setEnabled(false);
        ui->pushButton_Auto->setEnabled(false);
    }
}

void MainWindow::on_pushButton_Lap_clicked() // кнопка сделать круг
{
//    mas_table = new int[rows];
//    ui->tableWidget->setEnabled(true);
    mas_table[rows] = lap;
    ui->pushButton_Reset->setEnabled(true);

    ui->tableWidget->setColumnCount(1);
    // if (ui->tableWidget->item(rows,0) == nullptr)
   // { 
        QTableWidgetItem * twi = new QTableWidgetItem();
        twi->setFlags(Qt::ItemIsEditable);
        QFont font;
        font.setPixelSize(25);
        font.setBold(true);
        twi->setFont(font);
        ui->tableWidget->setItem(rows, 0, twi);
        ui->tableWidget->item(rows,0)->setText(gl_str);
        for (int i = 0; i < rows; i++)
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
        }
        ui->tableWidget->item(minLap(mas_table, rows), 0)->setBackgroundColor(Qt::green);
        ui->tableWidget->item(maxLap(mas_table, rows), 0)->setBackgroundColor(Qt::red);
   // }
    rows++;
    ui->tableWidget->setRowCount(rows+1);
    lap_timer->start(10);
    lap_counter = 0;
}

void MainWindow::on_pushButton_Reset_clicked() // кнопка сброса
{
    lap_counter = 0;
    ui->pushButton_Reset->setEnabled(false);
    for (int i = 0; i < rows; i++)
    {
        if (ui->tableWidget->item(i, 0) != nullptr) // проверка сущ-я ячейки
            ui->tableWidget->item(i, 0)->setText("");
        else
        {
            QTableWidgetItem * ti; // создание указателя
            ti = new QTableWidgetItem; // выделение памяти
            ui->tableWidget->setItem(i, 0, ti); // поместили ячейку в таблицу
        }
        ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
    }
//    on_pushButton_Stop_clicked();
    ui->tableWidget->setRowCount(1);
    rows = 0;
}


void MainWindow::on_spinBox_Wait_valueChanged(int sec)
{

    wait_counter = sec;

    QString str;
    int h, m; // часы, минуты, секунды

    str.clear();


    sec = wait_counter%60;

    m = wait_counter/60;
    h = m/60;
    m = m % 60;

    if (h < 10)
        str.append("0");
    str.append(QString::number(h));
    str.append(":");

    if (m < 10)
        str.append("0");
    str.append(QString::number(m));
    str.append(":");

    if (sec < 10)
        str.append("0");
    str.append(QString::number(sec));

//    str.append(".00");

    ui->lcdNumber_Wait->display(str);

}

//void MainWindow::on_spinBox_Start_valueChanged(int arg1)
//{
//    if (timer->isActive())
//    {
////        start_counter = ui->spinBox_Start->value();
//        start_counter = arg1;
//    }
//}

