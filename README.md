# Cpp-QT-VideoPlayer
C++和Qt库窗口视频播放器
#include <QApplication>
#include <QWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

这些是用于Qt应用程序的头文件，用于包含所需的类和函数。

class VideoPlayer : public QWidget {
    Q_OBJECT

这里定义了一个名为`VideoPlayer`的类，它是QWidget类的子类，并使用`Q_OBJECT`宏来启用Qt的元对象系统。

public:
    VideoPlayer(QWidget *parent = nullptr) : QWidget(parent) {

`VideoPlayer`类的构造函数，其中`parent`参数是一个指向父级窗口的指针（默认为`nullptr`）。


player = new QMediaPlayer(this);
videoWidget = new QVideoWidget(this);
player->setVideoOutput(videoWidget);

创建了`QMediaPlayer`和`QVideoWidget`实例，并将`QVideoWidget`设置为`QMediaPlayer`的视频输出。

QPushButton *openButton = new QPushButton("选择视频", this);
QPushButton *playButton = new QPushButton("播放", this);
QPushButton *pauseButton = new QPushButton("暂停", this);

创建了三个`QPushButton`实例，分别用于打开视频文件、播放和暂停操作。

QSlider *volumeSlider = new QSlider(Qt::Horizontal, this);
volumeSlider->setRange(0, 100);
volumeSlider->setValue(50);
player->setVolume(50);

创建了一个水平的`QSlider`实例，用于控制音量。设置了音量范围为0到100，初始值为50，并将该值同时设置给`QMediaPlayer`的音量属性。

QSlider *speedSlider = new QSlider(Qt::Horizontal, this);
speedSlider->setRange(50, 200);
speedSlider->setValue(100);

创建了一个水平的`QSlider`实例，用于控制速度。设置了速度范围为50%到200%，初始值为100。

connect(openButton, &QPushButton::clicked, this, &VideoPlayer::openVideo);
connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
connect(speedSlider, &QSlider::valueChanged, this, &VideoPlayer::setSpeed);

通过信号和槽连接，将按钮和滑块的操作与相应的功能函数进行关联。

QVBoxLayout *mainLayout = new QVBoxLayout(this);
QHBoxLayout *buttonLayout = new QHBoxLayout();
buttonLayout->addWidget(openButton);
buttonLayout->addWidget(playButton);
buttonLayout->addWidget(pauseButton);
mainLayout->addWidget(videoWidget);
mainLayout->addLayout(buttonLayout);
mainLayout->addWidget(volumeSlider);
mainLayout->addWidget(speedSlider);
setLayout(mainLayout);

创建了垂直和水平的布局管理器，并将视频窗口、按钮和滑块添加到相应的布局中，并将该布局设置为主窗口的布局。

void open

Video() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择视频文件");
    if (!fileName.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->play();
    }
}
`openVideo`函数是用于打开视频文件的槽函数。它通过调用`QFileDialog`的`getOpenFileName`函数来获取用户选择的视频文件的文件名，并使用`QMediaPlayer`的`setMedia`函数设置媒体内容为该文件，并调用`play`函数开始播放。

void setSpeed(int value) {
    qreal speed = static_cast<qreal>(value) / 100.0;
    player->setPlaybackRate(speed);
}

`setSpeed`函数是用于设置播放速度的槽函数。它接受一个整数参数`value`，表示滑块的值。根据滑块的值，将其转换为一个实数表示的速度，并使用`QMediaPlayer`的`setPlaybackRate`函数设置播放速度。

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VideoPlayer player;
    player.show();

    return app.exec();
}

`main`函数是程序的入口点。它创建了一个`QApplication`实例，并创建并显示了一个`VideoPlayer`窗口。最后，通过调用`app.exec()`来启动Qt的事件循环，使应用程序进入运行状态。

#include "main.moc"

这是为了让Qt的元对象编译器（MOC）处理`Q_OBJECT`宏，以支持信号和槽的连接。
