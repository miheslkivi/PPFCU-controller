/* Derived from Qt4 example software   "Local fortune client"
*
*  Controller and info program for Pac-person freespace continuum undiscreted
* ( PPFCU or p-pf-scu-d ) - Copyright (C) 2018 by Mikko Heiska
*
*
*/


/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/




#ifndef CLIENT_H
#define CLIENT_H

//#include <QWidget>

//#include <QDialog>
#include <QtWidgets>
#include <QtNetwork>

#include <qlocalsocket.h>
#include<vector>
//#include<QMessageBox>

using namespace std;

//static int vie;
struct boints
{
  char bb;
int sw;
bool init;
char sel;
};
union charintunion
{
    int sint;
    float flo;
    char merk[4];
};

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QLocalSocket;
QT_END_NAMESPACE
//static int lask;

#ifdef Q_WS_MAEMO_5
class Client : public QWidget
#else
class Client : public QDialog
#endif
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);
    void labswi(int swi, QLabel *lab  );
    void labswi2( int swi, QLabel *lab  );

    void labtextnum( QString tex,  double num, QLabel *lab );

    void buttonswi(bool swi, QPushButton *button  );
    void buttonswi2( float aaa, float bbb, bool swi, QPushButton *button  );

    void buttonsel(int sel, QPushButton *button  );
    void buttonsel2( int sel, QPushButton *button );
void clearfocuses(   );


  //  void swiboi(int pla , int vab1);
void setdgconst();

char fboi(uint pai );
void seboi(uint pai, int cou );

public slots:
//    void ilmo();

private slots:

    void laheta();
void slotghattbut();
void slotcenterviebut();

void slotclose();
void slotcloseboth();

void slotlghbut();

void slotsightbbut();

void slotsghbut();

void slotminewaitbut();

void slotspixubut();

void slotbrakebut();

void slotminecollectbut();

void slotsplonbut ();

void slotsafetyonbut();

void slotksuuntvhbut();

void slotasuuntvhbut ();

void slotlsuuntvhbut();

void slotmiskohbut ();

void slotmstbut ();

void slotmsmibut ();

void slothudbut();

void slotasthudbut();

void slotisohudbut();

void slothelptextonbut ();

void slotshortmesonbut();

void slotfreelobut() ;
void slotsanglebut();
void slotfullscbut();
void slotedgecebut();

void slotympybut();
void slotpausebut() ;
void slotnewgamebut() ;
void slotnewshipbut() ;
void slotzoom_plusbut() ;
void slotzoom_minusbut() ;
void slotreloadconfbut() ;
void slotminebut() ;
void slotdetonbut() ;
  void slotclearbbut() ;
void slotppicintbut() ;
void slotthrustbut() ;
void slotslowthrustbut() ;
void  slotminelay();

void  slotminevisible();
void  slotbervisible();
void  slotenervisible();
void  slotboxvisible();
void  slotexplvisible();

void  slotbercol();
void  slotenercol();
void  slotboxcol();



    void requestNewFortune( );
    void readFortune();
    void displayError(QLocalSocket::LocalSocketError socketError);
    void enableGetFortuneButton();
    void timerquit();
    void timb( );


private:
    QLabel *hostLabel;
    QLineEdit *hostLineEdit;
    QLabel *statusLabel;

    QLabel *nopkyl, *enerlabel, *spottedlab, *closelab, *closestlab, *ghinvlab, *hcmodelab, *reasonlab,
    *pacliveslab, *nofalab, *traillab, *ghost_modelab,
    *unpickedberlab, *berlab, *missileslab, *mineslab, *minesoutlab, *spinghostslab, *normalghostslab,
    *ghostcountlab, *fpslab, *shortmsglab,  *speedwarnlab, *fuelwarnlab, *minewarnlab, *misswarnlab,
    *finitefuellab, *spottednumlab_, *spotted_lios_lab_,  *spottedby_lab_, *tecounter_lab_, *setcou_lab_,
    *zoomlab_ , *velocityalab_, *velocityblab_, *pacxlab_, *pacylab_;


    QPushButton *quitButton, *quitbothbutton, *ghattbutton, *centerviebut, *lghbut, *sightbbut,
    *sghbut, *minewaitbut, *spixubut, *brakebut, *minecollectbut, *splonbut, *safetyonbut,
    *ksuuntvhbut, *asuuntvhbut, *lsuuntvhbut, *miskohbut, *mstbut, *msmibut, *hudbut, *asthudbut,
    *isohudbut, *helptextonbut,  *shortmesonbut, *freelobut,  *sanglebut,  *fullscbut,  *edgecebut, *pausebut,
    *ympybut, *newgamebut, *newshipbut, *zoom_plusbut, *zoom_minusbut, *reloadconfbut, *minebut, *detonbut,
    *clearbbut, *ppicintbut,  *thrustbut, *slowthrustbut, *minelaybut, *minevisiblebut, *bervisiblebut,
    *enervisiblebut, *boxvisiblebut, *explvisiblebut, *bercolbut, *enercolbut, *boxcolbut ;

//QRadioButton *minewaitbut;
//QToolButton *minewaitbut;

    QDialogButtonBox *buttonBoxa, *buttonBox1, *buttonBox2,  *buttonBox3, *buttonBox4, *buttonBox5 ;

    QLocalSocket *insocket;
    QLocalSocket *outsocket;

    QString currentFortune;
    quint16 blockSize;

    QTimer *receivetimer, *sendtimer, *messagetimer ;
bool ghatt_;
int ghatt_c_;

boints ghattboi_;
vector<boints> bointsli_;

//vector<QPushButton*> qpbvec_;

QPalette pal_on_, pal_off_, pal_unswit_ , pal_warning_, pal_warning2_, pal_normal_, pal_normal2_ ;
QColor onb_, ont_, offb_, offt_, unswb_, unswt_, warnb_, warnt_, warn2b_, warn2t_, norb_, nort_, norb2_, nort2_;


charintunion sbool_;
QByteArray qar_;
int coute_, boicount_;

int ghatt_pla_, centervie_pla_, minecollect_pla_,
sightb_pla_,
sgh_pla_,
minewait_pla_,
spixu_pla_,
brake_pla_,
splon_pla_,
safetyon_pla_,
ksuuntvh_pla_,
asuuntvh_pla_,
lsuuntvh_pla_,
miskoh_pla_,
mst_pla_,
msmi_pla_,
hud_pla_,
asthud_pla_,
isohud_pla_,
helptexton_pla_,
shortmeson_pla_,
freelo_pla_,
sangle_pla_,
fullsc_pla_,
edgece_pla_,
ympy_pla_, spotted_pla_,

shortmsg_pla_ ,
pause_pla_,
newgame_pla_,
newship_pla_,
zoom_plus_pla_,
zoom_minus_pla_,
reloadconf_pla_,
mine_pla_,
deton_pla_,
   clearb_pla_,
ppicint_pla_,
thrust_pla_,
slowthrust_pla_,
close_pla_,
ghinv_pla_,
hcmode_pla_,
reason_pla_,
paclives_pla_,
nofa_pla_,
trail_pla_,
ghost_mode_pla_,

ener_pla_, speed_pla_,
minelay_pla_,

fuelwarn_pla_, minewarn_pla_, misswarn_pla_,
mines_pla_,    miss_pla_,

norghostcount_pla_,   spinghostcount_pla_, ghostcount_pla_, ber_pla_, unber_pla_, tec_pla_, setcou_pla_,
 traffic_collision_velocity_pla_, speed_limiterf_pla_, zoom_pla_, pac1x1_pla_,  pac1y1_pla_,  velocitya_pla_,
    velocityb_pla_, minevisible_pla_, bervisible_pla_, enervisible_pla_, boxvisible_pla_, bercol_pla_,
enercol_pla_, boxcol_pla_, finitefuel_pla_, explvisible_pla_, spottednum_pla_, spotted_lios_pla_,  spottedby_pla_,
closest_pla_, mines_out_pla_,fps_pla_ , closeboth_pla_;


int bointslimax_, qbamax_;
/*
QLabel *nopkyl, *enerlabel, *spottedlab, *closelab, *closestlab, *ghinvlab, *hcmodelab, *reasonlab,
*pacliveslab, *nofalab, *traillab, *ghost_modelab,
*unpickedberlab, *missileslab, *mineslab, *minesoutlab, *spinghostslab, *normalghostslab,
*ghostcountlab, *fpslab, *shortmsglab,  *speedwarnlab, *fuelwarnlab, *minewarnlab, *misswarnlab,
*finitefuellab, *spottednumlab_, *spotted_lios_lab_,  *spottedby_lab_;
*/


int norghostcount_,
spinghostcount_,
ghostcount_,
ghost_mode_, ber_, unber_, tec_, spot_tec_, setcou_, mines_, minesout_, reason_,
missiles_, spottednum_, spotted_lios_,  spottedby_, shortmsg_;

float traffic_collision_velocity_, speed_limiterf_, zoom_, pac1x1_, pac1y1_, speed_, fuel_, velocitya_, velocityb_,
closest_, fps_ ;

/*
*nopkyl, *enerlabel,  *closestlab,

    *unpickedberlab, *missileslab, *mineslab, *minesoutlab, *spinghostslab, *normalghostslab,
    *ghostcountlab, *fpslab, *shortmsglab;
*/
int mestimer_, rea_, erco_, ercomax_;
QMessageBox *mesbo_;
QString *trx_;
QString outservername_;
QString inservername_;
};

#endif
