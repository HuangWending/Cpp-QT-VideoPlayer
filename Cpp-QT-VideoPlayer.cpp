#include <QApplication>
#include <QWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class VideoPlayer : public QWidget {
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr) : QWidget(parent) {
        // 创建媒体播放器和视频显示窗口
        player = new QMediaPlayer(this);
        videoWidget = new QVideoWidget(this);
        player->setVideoOutput(videoWidget);

        // 创建控制按钮
        QPushButton *openButton = new QPushButton("选择视频", this);
        QPushButton *playButton = new QPushButton("播放", this);
        QPushButton *pauseButton = new QPushButton("暂停", this);

        // 创建声音控制滑块
        QSlider *volumeSlider = new QSlider(Qt::Horizontal, this);
        volumeSlider->setRange(0, 100);
        volumeSlider->setValue(50);
        player->setVolume(50); // 默认音量为50%

        // 创建速度控制滑块
        QSlider *speedSlider = new QSlider(Qt::Horizontal, this);
        speedSlider->setRange(50, 200); // 可调整速度范围为50%到200%
        speedSlider->setValue(100); // 默认速度为正常速度

        // 连接按钮信号和槽函数
        connect(openButton, &QPushButton::clicked, this, &VideoPlayer::openVideo);
        connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
        connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
        connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
        connect(speedSlider, &QSlider::valueChanged, this, &VideoPlayer::setSpeed);

        // 创建布局管理器
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
    }

public slots:
    void openVideo() {
        QString fileName = QFileDialog::getOpenFileName(this, "选择视频文件");
        if (!fileName.isEmpty()) {
            player->setMedia(QUrl::fromLocalFile(fileName));
            player->play();
        }
    }

    void setSpeed(int value) {
        qreal speed = static_cast<qreal>(value) / 100.0;
        player->setPlaybackRate(speed);
    }

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VideoPlayer player;
    player.show();

    return app.exec();
}

#include "main.moc"
