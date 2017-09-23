#ifndef G_MAIN_WINDOW_H
#define G_MAIN_WINDOW_H

// Qt header
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QtGui>
#include <QThread>
#include <QPixmap>
#include <QGraphicsScene>

// stl
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <boost/filesystem.hpp>

// opencv header
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// local
#include "imgproc/util_funcs.h"
#include "thread/c_t_imgload.h"
#include "thread/c_t_lcmsubscr.h"
#include "thread/c_t_monitor.h"
#include "thread/c_t_grab_vlp_16_hr.h"
#include "3d_view/c_3d_viewer.h"

#include "lcm/c_lcm_handler.h"

using namespace std;

namespace Ui {
class G_MAIN_WINDOW;
}

class G_MAIN_WINDOW : public QMainWindow
{
    Q_OBJECT

public:
    explicit G_MAIN_WINDOW(QWidget *parent = 0);
    ~G_MAIN_WINDOW();

private slots:
    void on_pushButton_start_load_clicked();

    void on_pushButton_set_img_loadpath_clicked();

    void on_pushButton_set_img_savepath_clicked();

    void on_pushButton_save_img_clicked();

private:
    Ui::G_MAIN_WINDOW *ui;

// thread
private:
    C_T_MONITOR* c_t_monitor = new C_T_MONITOR;
    C_T_IMGLOAD* c_t_imgload;
    C_T_LCMSUBSCR* c_t_lcmsubscr_cam = new C_T_LCMSUBSCR;
    C_T_GRAB_VLP_16_HR* c_t_grab_vlp_16_hr;

private:
    QMutex mtx_monitor;
    QMutex mtx_grab_cam[8];
    QMutex mtx_grab_lidar;

    lcm::LCM m_lcm_obj;
    C_LCM_CAM m_lcm_cam_obj_recv;

    uint m_cam_num = 0;

    cv::Mat m_ori_img[8];
    cv::Mat m_disp_img[8];
    QImage m_disp_img_q[8];
    QPixmap m_disp_img_p[8];
    QGraphicsScene *m_disp_img_scene = new QGraphicsScene[8];
    QGraphicsView *m_graphicsview_list[8];
    cv::Size m_disp_size;

    string m_img_loadpath_str;
    string m_img_savepath_str;

    ulong m_timestamp;

    C_3D_VIEWER* c_3d_viewer_obj = new C_3D_VIEWER;


public slots:
    void SLOT_C_T_MONITOR_2_MAIN();
    void SLOT_C_T_IMGLOAD_2_MAIN_1(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_2(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_3(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_4(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_5(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_6(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_7(cv::Mat _recv_img);
    void SLOT_C_T_IMGLOAD_2_MAIN_8(cv::Mat _recv_img);
    void SLOT_C_T_GRAB_VLP_16_HR_2_MAIN(PointCloudT _cloud);

signals:
    void SIG_MAIN_2_C_T_IMGLOAD_1(string);
    void SIG_MAIN_2_C_T_IMGLOAD_2(string);
    void SIG_MAIN_2_C_T_IMGLOAD_3(string);
    void SIG_MAIN_2_C_T_IMGLOAD_4(string);
    void SIG_MAIN_2_C_T_IMGLOAD_5(string);
    void SIG_MAIN_2_C_T_IMGLOAD_6(string);
    void SIG_MAIN_2_C_T_IMGLOAD_7(string);
    void SIG_MAIN_2_C_T_IMGLOAD_8(string);
    void SIG_MAIN_2_C_T_GRAB_VLP_16_HR_PAUSE(bool _pause_status);

};

#endif // G_MAIN_WINDOW_H
