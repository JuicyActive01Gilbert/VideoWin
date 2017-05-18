#ifndef VIDEOWIN_H
#define VIDEOWIN_H

#include <QWidget>
#include <QPaintEvent>
#define DEFALUT_VOLUME 50 //Ĭ��������С,��Χ��0-100

class QVideoWidget;
class QMediaPlayer;
class QMediaPlaylist;

class VideoWin : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWin(QWidget *parent = 0);
	~VideoWin();
	
	void setFilePaths(QStringList lstPaths);//������Ƶ·���б�
	void setVolume(int value);//����������С����Χ:0-100��
	int getVoluem();//��ȡ������С
	void startPlay();//��ʼ����
	void pausePlay();//��ͣ
	void stopPlay();//ֹͣ
	void upMedia();//��һ����Ƶ
	void nextMedia();//��һ����Ƶ
	void changeVideoPosition(qint64 position);//�ı䵱ǰ��Ƶ����ʱ�������Ž��ȿ��ƣ�
	QString getCurrentVideoPath();//��ȡ��ǰ���ŵ���Ƶ��·��

signals:
	void signalMediaTotalTime(qint64);//��ȡ��ǰ���ŵ���Ƶ��ʱ��(��λ������)
	void signalMediaPosition(qint64);//��ȡ��ǰ��Ƶ��ǰ���ȣ���λ�����룩
protected:
	void initialize();//��ʼ��
	void paintEvent(QPaintEvent* pEvent);
protected slots:

private:
	QMediaPlayer* m_pMediaPlayer;
	QMediaPlaylist* m_pMediaList;//��Ƶ����
	QVideoWidget* m_pVideoWin;

	qint64 m_nTotalDuration;//��Ƶ��ʱ������λ������
	qint64 m_nCurrentDuration;//��ǰ����ʱ������λ������
	int m_nVolume;//��ǰ����
	int m_nIndexMedia;//��ǰ�ǵڼ�����Ƶ(���ڿ�����һ����Ƶ����һ����Ƶ���л�)
};

#endif // VIDEOWIN_H
