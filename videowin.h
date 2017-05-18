#ifndef VIDEOWIN_H
#define VIDEOWIN_H

#include <QWidget>
#include <QPaintEvent>
#define DEFALUT_VOLUME 50 //默认音量大小,范围：0-100

class QVideoWidget;
class QMediaPlayer;
class QMediaPlaylist;

class VideoWin : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWin(QWidget *parent = 0);
	~VideoWin();
	
	void setFilePaths(QStringList lstPaths);//设置视频路径列表
	void setVolume(int value);//设置音量大小（范围:0-100）
	int getVoluem();//获取音量大小
	void startPlay();//开始播放
	void pausePlay();//暂停
	void stopPlay();//停止
	void upMedia();//上一个视频
	void nextMedia();//下一个视频
	void changeVideoPosition(qint64 position);//改变当前视频播放时长（播放进度控制）
	QString getCurrentVideoPath();//获取当前播放的视频的路径

signals:
	void signalMediaTotalTime(qint64);//获取当前播放的视频的时长(单位：毫秒)
	void signalMediaPosition(qint64);//获取当前视频当前进度（单位：毫秒）
protected:
	void initialize();//初始化
	void paintEvent(QPaintEvent* pEvent);
protected slots:

private:
	QMediaPlayer* m_pMediaPlayer;
	QMediaPlaylist* m_pMediaList;//视频播单
	QVideoWidget* m_pVideoWin;

	qint64 m_nTotalDuration;//视频总时长，单位：毫秒
	qint64 m_nCurrentDuration;//当前播放时长，单位：毫秒
	int m_nVolume;//当前音量
	int m_nIndexMedia;//当前是第几个视频(用于控制上一个视频、下一个视频的切换)
};

#endif // VIDEOWIN_H
