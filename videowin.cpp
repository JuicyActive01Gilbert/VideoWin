#include "videowin.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>

VideoWin::VideoWin(QWidget *parent) 
	: QWidget(parent)
{
	m_pMediaPlayer = NULL;
	m_pMediaList = NULL;
	m_pVideoWin = NULL;
	m_nTotalDuration = 0;
	m_nCurrentDuration = 0;
	m_nIndexMedia = 0;
	m_nVolume = DEFALUT_VOLUME;

	initialize();
}


VideoWin::~VideoWin()
{

}

void VideoWin::setFilePaths(QStringList lstPaths)
{
	if (lstPaths.count() <= 0)
	{
		return;
	}
	m_pMediaList->clear();
	for (int i = 0; i < lstPaths.count();i++)
	{
		m_pMediaList->addMedia(QUrl::fromLocalFile(lstPaths.at(i)));
	}
	//默认先播放第一个
	if (m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	m_pMediaList->setCurrentIndex(0);
	m_nIndexMedia = 0;
}

void VideoWin::setVolume(int value)
{
	if (m_pMediaPlayer == NULL)
	{
		return;
	}
	m_pMediaPlayer->setVolume(value);
}

int VideoWin::getVoluem()
{
	if (m_pMediaPlayer == NULL)
	{
		return 0;
	}
	return m_pMediaPlayer->volume();
}

void VideoWin::startPlay()
{
	if (m_pMediaPlayer == NULL ||\
		m_pMediaPlayer->state() == QMediaPlayer::PlayingState ||\
		m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	m_pMediaPlayer->play();
	m_nTotalDuration = m_pMediaPlayer->duration();
}

void VideoWin::pausePlay()
{
	if (m_pMediaPlayer == NULL || \
		m_pMediaPlayer->state() == QMediaPlayer::PausedState || \
		m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	m_pMediaPlayer->pause();
}

void VideoWin::stopPlay()
{
	if (m_pMediaPlayer == NULL || \
		m_pMediaPlayer->state() == QMediaPlayer::StoppedState || \
		m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	m_pMediaPlayer->stop();
	m_nCurrentDuration = 0;

}

void VideoWin::upMedia()
{
	if (m_pMediaPlayer == NULL || \
		m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	stopPlay();//先停止播放当前视频
	m_nIndexMedia--;
	if (m_nIndexMedia < 0)
	{
		m_nIndexMedia = 0;
	}
	m_pMediaList->setCurrentIndex(m_nIndexMedia);
	startPlay();//重新播放新的视频
}

void VideoWin::nextMedia()
{
	if (m_pMediaPlayer == NULL || \
		m_pMediaList->mediaCount() <= 0)
	{
		return;
	}
	stopPlay();//先停止播放当前视频
	m_nIndexMedia++;
	if (m_nIndexMedia >= m_pMediaList->mediaCount())
	{
		m_nIndexMedia = m_pMediaList->mediaCount() - 1;
	}
	m_pMediaList->setCurrentIndex(m_nIndexMedia);
	startPlay();//重新播放新的视频
}

void VideoWin::changeVideoPosition(qint64 position)
{
	m_pMediaPlayer->setPosition(position);
}
QString VideoWin::getCurrentVideoPath()
{
	QString path;
	path.clear();
	if (m_pMediaPlayer == NULL || \
		m_pMediaList->mediaCount() <= 0)
	{
		return path;
	}

	path = m_pMediaList->currentMedia().canonicalUrl().toString();
	return path;
}

void VideoWin::initialize()
{
	m_pMediaPlayer = new QMediaPlayer(this);
	connect(m_pMediaPlayer, SIGNAL(durationChanged(qint64)), this, SIGNAL(signalMediaTotalTime(qint64)));
	connect(m_pMediaPlayer, SIGNAL(positionChanged(qint64)), this, SIGNAL(signalMediaPosition(qint64)));
	m_pMediaList = new QMediaPlaylist(this);
	//设置播放窗口
	m_pVideoWin = new QVideoWidget(this);
	m_pVideoWin->setGeometry(0,0,this->width(), this->height());
	m_pMediaPlayer->setVideoOutput(m_pVideoWin);
	m_pVideoWin->show();
	m_pMediaPlayer->setVolume(m_nVolume);
	m_pMediaPlayer->setPlaylist(m_pMediaList);

}


void VideoWin::paintEvent(QPaintEvent* pEvent)
{
	if (m_pVideoWin != NULL)
	{
		m_pVideoWin->setGeometry(0, 0, this->width(), this->height());
	}
	QWidget::paintEvent(pEvent);
}

