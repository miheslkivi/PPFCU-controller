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




#include <QtGui>
#include <QtNetwork>
#include <iostream>
#include <string>
#include<sstream>
using namespace std;
#include "client.h"



double prec( double val, double pre )
{
    double aa;
    int ival;

    ival=val/pre;

    aa=ival*pre;

    return aa;
}
string numtochar( double num )
{
    string snum;
    stringstream snumss;
    snumss.precision(3);
    snumss << num;
    snumss >> snum;
    //cout << "  ----------" << snum.c_str() << endl;
    return snum;

}

int qbatoint(  int plax, QByteArray &qra )
{
    charintunion mru;
    int pla=plax*2;

    if( pla+3>=qra.size() )
    {
        cout << endl << " qbatoint: error: " << pla+3 << " size=" << qra.size() << endl;
    }
    mru.merk[0]=qra.at( pla+0);
    mru.merk[1]=qra.at( pla+1);
    mru.merk[2]=qra.at( pla+2);
    mru.merk[3]=qra.at( pla+3);
    return mru.sint;
}
float qbatofloat(  int plax, QByteArray &qra )
{
    charintunion mru;
    int pla=plax*2;
    if( pla+3>=qra.size() )
    {
        cout << endl << " qbatofloat: error: " << pla+3 << " size=" << qra.size() << endl;
    }

    mru.merk[0]=qra.at( pla+0);
    mru.merk[1]=qra.at( pla+1);
    mru.merk[2]=qra.at( pla+2);
    mru.merk[3]=qra.at( pla+3);
    return mru.flo ;
}


QByteArray anluqbli( int aa, int bb, int cc )
{
    QByteArray tul;
    tul.push_back( aa );
    tul.push_back( bb );
    tul.push_back( cc );
    tul.push_back( 'n' );

    return tul;
}
QByteArray qbachar( char state, char act )
{
    QByteArray tul;
    tul.push_back( state );
    tul.push_back( act );

    return tul;

}
int qbarswi( int pla, QByteArray &qba )
{
    if( pla*2>=qba.size() )
    {
        cout << endl << " qbarswi: error: " << pla*2 << " size=" << qba.size() << endl;
    }
    return qba.at( ( pla*2 ) );

}


void flipb( char &var )
{
    if( var)
        var=0;
    else
        var=1;

}

void flipboints(  boints &bh )
{
    if( bh.sw==0 and bh.bb!=2)
    {
        if( bh.bb==1 )
        {
            bh.bb=0;
        }
        else
        {
            bh.bb=1;
        }
        bh.sw=1;

    }
}
char Client::fboi( uint pai )
{
    if( pai<bointsli_.size()  )
    {
        flipboints( bointsli_.at( pai ) );
    }
    else
    {
        cout << endl << " fboi: error: " << pai << " size=" << bointsli_.size() << endl;
    }
    return bointsli_.at( pai ).bb;
}

void selboints( boints &bh, int cou )
{
    if( bh.sw==0 )
    {
        if( bh.bb<cou-1 )
        {
            bh.bb++;
        }
        else
        {
            bh.bb=0;
        }
        bh.sw=1;

    }
}
void Client::seboi( uint pai, int cou )
{
    if( pai<bointsli_.size()  )
    {
        selboints( bointsli_.at( pai ), cou );
    }
    else
    {
        cout << endl << " seboi: error: " << pai << " size=" << bointsli_.size() << endl;

    }
}


Client::Client(QWidget *parent)
    : QDialog(parent)

{
  setAutoFillBackground(1 );
  QColor bordercol( 8, 22, 18 );

  QPalette borderpal(Qt::darkGreen, bordercol, QColor( 28, 18, 18 ),
                     QColor( 24, 64, 6 ), Qt::black, Qt::green, QColor( 8, 22, 12 ) );
 setPalette( borderpal );

    coute_=0;
    boicount_=0;
    spot_tec_=-1111;
    mestimer_=0;
    trx_=new QString(" error ");
    setdgconst();

    onb_=QColor( 0,200, 0 );
    ont_= QColor( 0, 0, 0 );

    offb_= QColor( 50, 50, 50 );
    offt_= QColor( 0, 0, 0 );

    unswb_= QColor( 0, 0, 255 );
    unswt_= QColor( 10, 0, 0 );

    warnb_= QColor( 255, 0, 0 );
    warnt_= QColor( 0, 0, 100 );

    warn2b_= QColor( 255, 180, 0 );
    warn2t_= QColor( 0, 0, 255 );

    //warn2b_= QColor( 255, 180, 0 );
    //  warn2t2_= QColor( 0, 0, 255 );

    norb_= QColor( 10, 20, 10 );
    nort_= QColor( 30, 30, 30 );

    norb2_= QColor( 10, 20, 10 );
    nort2_= QColor( 130, 150, 130 );

    pal_on_=QPalette(  ont_ , onb_, Qt::white, Qt::yellow,
                       Qt::cyan, ont_, Qt::green, Qt::lightGray, onb_  );

    pal_off_=QPalette(  offt_ , offb_, Qt::darkGray, Qt::darkYellow,
                        Qt::darkCyan, offt_, Qt::darkGreen, Qt::gray, offb_  );

    pal_unswit_=QPalette(  Qt::red , unswb_, Qt::blue, Qt::darkYellow,
                           Qt::darkCyan, unswt_, Qt::darkGreen, Qt::blue, Qt::black  );


    pal_warning_=QPalette(  Qt::white , warnb_, Qt::darkGray, Qt::darkYellow,
                            Qt::darkCyan, warnt_, Qt::darkGreen, Qt::gray, warnb_  );

    pal_warning2_=QPalette(  warn2t_ , warn2b_, Qt::darkGray, Qt::darkYellow,
                             Qt::darkCyan, warn2t_, Qt::darkGreen, Qt::gray,  warn2b_ );


    pal_normal_=QPalette(  norb_ , Qt::darkBlue, Qt::black, Qt::darkYellow,
                           Qt::darkCyan, Qt::darkMagenta, Qt::darkGreen, Qt::black, nort_  );

    pal_normal2_=QPalette(  nort2_ , Qt::darkBlue, Qt::black, Qt::darkYellow,
                            Qt::darkCyan, Qt::darkMagenta, Qt::darkGreen, Qt::black, norb2_  );



    outservername_="pacserverout";
inservername_="pacserverin";

    //  statusLabel = new QLabel(tr("This examples requires that you run the "
    //                            "Fortune Server example as well."));

    int ite;
    nopkyl = new QLabel("--");
    enerlabel= new QLabel("--");

    ghinvlab=new QLabel("ghinv");
    hcmodelab=new QLabel("hcm ");

    spottedlab=new QLabel("spotted");

    closelab=new QLabel("close" );
    closestlab=new QLabel( );
    ghinvlab=new QLabel("ghinv" );
    hcmodelab=new QLabel("hcmode" );
    reasonlab=new QLabel("reason");
    pacliveslab=new QLabel("paclives" );
    nofalab=new QLabel("nofa" );
    traillab=new QLabel("trail" );
    ghost_modelab=new QLabel("ghost_mode" );
    unpickedberlab=new QLabel("unpickedber" );
    berlab=new QLabel("ber" );
    missileslab=new QLabel("missiles" );
    mineslab=new QLabel("mines");
    minesoutlab=new QLabel("minesout" );
    spinghostslab=new QLabel("spinghosts" );
    normalghostslab=new QLabel("normalghosts" );
    ghostcountlab=new QLabel("ghostcount" );
    fpslab=new QLabel("fps" );
    shortmsglab=new QLabel("shortmsg" );

    speedwarnlab=new QLabel("speed" );
    fuelwarnlab=new QLabel("fuel" );
    minewarnlab =new QLabel("min" );
    misswarnlab=new QLabel("mis" );
    finitefuellab=new QLabel("finitefuel" );

    spottednumlab_ =new QLabel("spottednum" );
    spotted_lios_lab_ =new QLabel("spotted_lios" );
    spottedby_lab_=new QLabel("spottedby" );
    tecounter_lab_=new QLabel("tecounter" );
    setcou_lab_=new QLabel("setcou" );
    zoomlab_=new QLabel("zoom" );
    velocityalab_ =new QLabel("vela" );
    velocityblab_=new QLabel("velb" );

    pacxlab_=new QLabel("pacx" );
    pacylab_ =new QLabel("pacy" );

    spottedlab->setAutoFillBackground(true);
    closelab->setAutoFillBackground(true);
    closestlab->setAutoFillBackground(true);
    ghinvlab->setAutoFillBackground(true);
    hcmodelab->setAutoFillBackground(true);
    reasonlab->setAutoFillBackground(true);
    pacliveslab->setAutoFillBackground(true);
    nofalab->setAutoFillBackground(true);
    traillab->setAutoFillBackground(true);
    ghost_modelab->setAutoFillBackground(true);
    unpickedberlab->setAutoFillBackground(true);
    berlab->setAutoFillBackground(true);
    missileslab->setAutoFillBackground(true);
    mineslab->setAutoFillBackground(true);
    minesoutlab->setAutoFillBackground(true);
    spinghostslab->setAutoFillBackground(true);
    normalghostslab->setAutoFillBackground(true);
    ghostcountlab->setAutoFillBackground(true);
    fpslab->setAutoFillBackground(true);
    shortmsglab->setAutoFillBackground(true);

    speedwarnlab->setAutoFillBackground(true);
    fuelwarnlab->setAutoFillBackground(true);
    minewarnlab->setAutoFillBackground(true);
    misswarnlab->setAutoFillBackground(true);
    finitefuellab->setAutoFillBackground(true);

    spottednumlab_ ->setAutoFillBackground(true);
    spotted_lios_lab_ ->setAutoFillBackground(true);
    spottedby_lab_->setAutoFillBackground(true);
    tecounter_lab_->setAutoFillBackground(true);
    setcou_lab_->setAutoFillBackground(true);
    zoomlab_->setAutoFillBackground(true);
    velocityalab_->setAutoFillBackground(true);
    velocityblab_->setAutoFillBackground(true);

    pacxlab_->setAutoFillBackground(true);
    pacylab_->setAutoFillBackground(true);



    nopkyl->setFixedWidth(150);

    closestlab->setFixedWidth(150);


    ghinvlab->setFixedSize( 80, 22 );
    hcmodelab->setFixedSize( 80, 22 );
    ghostcountlab->setFixedSize( 80, 22 );
    traillab->setFixedSize( 80, 22 );
    pacliveslab->setFixedSize( 120, 22 );
    nofalab->setFixedSize( 120, 22 );
    finitefuellab->setFixedSize(  120, 22);

    // enerlabel->setFixedWidth(350);
    //    lab1->setFixedWidth(350);

    QFont labelFont( "monospace", 15 );
    QFont swfont( "courier", 15 );

    nopkyl->setFont( labelFont );
    enerlabel->setFont( labelFont );

    spottedlab->setFont( labelFont );
    closelab->setFont( swfont );
    closestlab->setFont( labelFont );
    ghinvlab->setFont( swfont );
    hcmodelab->setFont( swfont );
    reasonlab->setFont( labelFont );
    pacliveslab->setFont( labelFont );
    nofalab->setFont( labelFont );
    traillab->setFont( labelFont );
    ghost_modelab->setFont( labelFont );
    unpickedberlab->setFont( labelFont );
    berlab->setFont( labelFont );
    missileslab->setFont( labelFont );
    mineslab->setFont( labelFont );
    minesoutlab->setFont( labelFont );
    spinghostslab->setFont( labelFont );
    normalghostslab->setFont( labelFont );
    ghostcountlab->setFont( labelFont );
    fpslab->setFont( labelFont );
    shortmsglab->setFont( labelFont );

    speedwarnlab->setFont( swfont );
    fuelwarnlab->setFont( swfont );
    minewarnlab->setFont( swfont );
    misswarnlab->setFont( swfont );
    finitefuellab->setFont( swfont );

    spottednumlab_ ->setFont( labelFont );
    spotted_lios_lab_ ->setFont( labelFont );
    spottedby_lab_->setFont( labelFont );
    tecounter_lab_->setFont( labelFont );
    setcou_lab_->setFont( labelFont );
    zoomlab_->setFont( labelFont );

    velocityalab_ ->setFont( labelFont );
    velocityblab_->setFont( labelFont );
    pacxlab_->setFont( labelFont );
    pacylab_->setFont( labelFont );

    nopkyl-> setScaledContents (1);
    enerlabel-> setScaledContents (1);
    closestlab->setScaledContents(1);


    ghatt_=0;
    ghatt_c_=0;

    ghattboi_.bb=0;
    ghattboi_.sw=0;
    ghattboi_.init=0;
    ghattboi_.sel=0;
    for( ite=0 ; ite<bointslimax_ ; ite++ )
    {
        bointsli_.push_back( ghattboi_ );
    }



    quitButton = new QPushButton(tr("Quit"));
    quitbothbutton = new QPushButton(tr("Quitboth"));

    ghattbutton =  new QPushButton( "ghatt" );



    centerviebut=  new QPushButton( "centervie" );
    lghbut=  new QPushButton( "lgh" );
    sightbbut=  new QPushButton( "sightb" );

    sghbut=  new QPushButton( "sgh" );
    minewaitbut=  new QPushButton( "minewait"  );
    spixubut=  new QPushButton( "spixu" );
    brakebut=  new QPushButton( "brake" );
    minecollectbut=  new QPushButton( "minecollect" );
    splonbut=  new QPushButton( "speed limiter" );
    safetyonbut=  new QPushButton( "safetyon" );
    ksuuntvhbut=  new QPushButton( "ksuuntvh" );
    asuuntvhbut=  new QPushButton( "asuuntvh" );
    lsuuntvhbut=  new QPushButton( "lsuuntvh" );
    miskohbut=  new QPushButton( "miskoh" );
    mstbut=  new QPushButton( "mouseste" );
    msmibut=  new QPushButton( "msmi" );
    hudbut=  new QPushButton( "hud" );
    asthudbut=  new QPushButton( "asthud" );
    isohudbut=  new QPushButton( "isohud" );
    helptextonbut=  new QPushButton( "helptexton" );
    shortmesonbut=  new QPushButton( "shortmeson" );

    freelobut=  new QPushButton( "freelo" );
    sanglebut=  new QPushButton( "sangle" );
    fullscbut=  new QPushButton( "fullsc" );
    edgecebut=  new QPushButton( "edgece" );
    ympybut= new QPushButton( "velmet x" );

    pausebut= new QPushButton( "pause" );
    newgamebut= new QPushButton( "newgame" );
    newshipbut= new QPushButton( "newship" );
    zoom_plusbut= new QPushButton( "zoom_plus" );
    zoom_minusbut= new QPushButton( "zoom_minus" );
    reloadconfbut= new QPushButton( "reloadconf" );
    minebut= new QPushButton( "mine" );
    detonbut= new QPushButton( "deton" );
    clearbbut= new QPushButton( "clearb" );
    ppicintbut= new QPushButton( "ppicint" );
    thrustbut= new QPushButton( "thrust" );
    slowthrustbut= new QPushButton( "slowthrust" );
    minelaybut= new QPushButton( "minelay" );

    minevisiblebut= new QPushButton("minevisi" );
    bervisiblebut= new QPushButton( "bervisi" );
    enervisiblebut= new QPushButton( "enervisi" );
    boxvisiblebut= new QPushButton("boxvisi" );
    explvisiblebut= new QPushButton("explvisi" );
    bercolbut= new QPushButton("bercol" );
    enercolbut= new QPushButton("enercol" );
    boxcolbut = new QPushButton( "boxcol" );


    /*

       takeset
  */


    buttonBoxa = new QDialogButtonBox( Qt::Vertical );
    buttonBox1 = new QDialogButtonBox( Qt::Vertical );
    buttonBox2 = new QDialogButtonBox( Qt::Vertical );
    buttonBox3 = new QDialogButtonBox( Qt::Vertical );
    buttonBox4 = new QDialogButtonBox( Qt::Vertical );
    buttonBox5 = new QDialogButtonBox( Qt::Vertical );


    buttonBoxa->addButton( quitButton, QDialogButtonBox::RejectRole);
    buttonBoxa->addButton( quitbothbutton, QDialogButtonBox::RejectRole);

    buttonBox1->addButton( ghattbutton, QDialogButtonBox::RejectRole);
  //  buttonBox1->addButton( centerviebut, QDialogButtonBox::RejectRole);
 //   buttonBox1->addButton( lghbut, QDialogButtonBox::RejectRole);
//    buttonBox1->addButton( sightbbut, QDialogButtonBox::RejectRole);
//    buttonBox1->addButton( sghbut, QDialogButtonBox::RejectRole);

    buttonBox1->addButton( boxvisiblebut, QDialogButtonBox::RejectRole);
    buttonBox1->addButton( bercolbut, QDialogButtonBox::RejectRole);
    buttonBox1->addButton( enercolbut, QDialogButtonBox::RejectRole);
    buttonBox1->addButton(  boxcolbut , QDialogButtonBox::RejectRole);

    buttonBox2->addButton( minewaitbut, QDialogButtonBox::RejectRole);
   // buttonBox2->addButton( spixubut, QDialogButtonBox::RejectRole);
    buttonBox2->addButton( brakebut, QDialogButtonBox::RejectRole);
    buttonBox2->addButton( minecollectbut, QDialogButtonBox::RejectRole);
    buttonBox2->addButton( splonbut, QDialogButtonBox::RejectRole);
    buttonBox2->addButton( safetyonbut, QDialogButtonBox::RejectRole);

    buttonBox2->addButton( minevisiblebut, QDialogButtonBox::RejectRole);
    buttonBox2->addButton( bervisiblebut  , QDialogButtonBox::RejectRole);
    buttonBox2->addButton(  enervisiblebut , QDialogButtonBox::RejectRole);

    buttonBox3->addButton( ksuuntvhbut, QDialogButtonBox::RejectRole);
    buttonBox3->addButton( asuuntvhbut, QDialogButtonBox::RejectRole);
    buttonBox3->addButton( lsuuntvhbut, QDialogButtonBox::RejectRole);
    buttonBox3->addButton( miskohbut, QDialogButtonBox::RejectRole);
    buttonBox3->addButton( mstbut, QDialogButtonBox::RejectRole);

    buttonBox3->addButton( ympybut, QDialogButtonBox::RejectRole);
    buttonBox3->addButton( explvisiblebut, QDialogButtonBox::RejectRole);


  //  buttonBox4->addButton( msmibut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton( hudbut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton( asthudbut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton( isohudbut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton( helptextonbut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton( shortmesonbut, QDialogButtonBox::RejectRole);


    buttonBox4->addButton(freelobut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton(        sanglebut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton(       fullscbut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton(        edgecebut, QDialogButtonBox::RejectRole);
    buttonBox4->addButton(  minelaybut, QDialogButtonBox::RejectRole);

    buttonBox5->addButton(  pausebut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(     newgamebut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        newshipbut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        zoom_plusbut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        zoom_minusbut,  QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        reloadconfbut,  QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        minebut,  QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        detonbut,   QDialogButtonBox::RejectRole);
    buttonBox5->addButton(    clearbbut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        ppicintbut, QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        thrustbut,  QDialogButtonBox::RejectRole);
    buttonBox5->addButton(        slowthrustbut, QDialogButtonBox::RejectRole);
        quitButton->setAutoFillBackground(true);
quitButton->clearFocus();

/*
    enerlabel->setAutoFillBackground(true);
    nopkyl->setAutoFillBackground(true);

    ghattbutton ->setAutoFillBackground(true);
    centerviebut->setAutoFillBackground(true);
    lghbut->setAutoFillBackground(true);
    sightbbut->setAutoFillBackground(true);
    sghbut->setAutoFillBackground(true);
  //  minewaitbut->setAutoFillBackground(true);
   //  minewaitbut->setCheckable(0);


    spixubut->setAutoFillBackground(true);
    brakebut->setAutoFillBackground(true);
    minecollectbut->setAutoFillBackground(true);
    splonbut->setAutoFillBackground(true);
    safetyonbut->setAutoFillBackground(true);
    ksuuntvhbut->setAutoFillBackground(true);
    asuuntvhbut->setAutoFillBackground(true);
    lsuuntvhbut->setAutoFillBackground(true);
    miskohbut->setAutoFillBackground(true);
    mstbut->setAutoFillBackground(true);
    msmibut->setAutoFillBackground(true);
    hudbut->setAutoFillBackground(true);
    asthudbut->setAutoFillBackground(true);
    isohudbut->setAutoFillBackground(true);
    helptextonbut->setAutoFillBackground(true);
    shortmesonbut   ->setAutoFillBackground(true);

    freelobut->setAutoFillBackground(true);
    sanglebut->setAutoFillBackground(true);
    fullscbut->setAutoFillBackground(true);
    edgecebut->setAutoFillBackground(true);
    ympybut->setAutoFillBackground(true);

    pausebut->setAutoFillBackground(true);
    newgamebut->setAutoFillBackground(true);
    newshipbut->setAutoFillBackground(true);
    zoom_plusbut->setAutoFillBackground(true);
    zoom_minusbut->setAutoFillBackground(true);
    reloadconfbut->setAutoFillBackground(true);
    minebut->setAutoFillBackground(true);
    detonbut->setAutoFillBackground(true);
    clearbbut->setAutoFillBackground(true);
    ppicintbut->setAutoFillBackground(true);
    thrustbut->setAutoFillBackground(true);
    slowthrustbut->setAutoFillBackground(true);
    minelaybut->setAutoFillBackground(true);
    explvisiblebut->setAutoFillBackground(true);
*/


    cout << " cons " << endl;




    //  connect( centerviebut , SIGNAL( clicked() ), this, SLOT( slotcenterviebutt()  ) );

    //connect( lghbut , SIGNAL( clicked() ), this, SLOT( slotlghbut()  ) );
    // connect( sightbbut , SIGNAL( clicked() ), this, SLOT( slotsightbbut()  ) );


    insocket = new QLocalSocket(this);
    outsocket = new QLocalSocket(this);

    receivetimer = new QTimer(this);
    sendtimer = new QTimer(this);
    messagetimer= new QTimer(this);
    connect( receivetimer, SIGNAL(timeout()), this, SLOT( requestNewFortune()  ) );
    connect( sendtimer, SIGNAL(timeout()), this, SLOT( laheta()  ) );

    connect( messagetimer, SIGNAL(timeout()), this, SLOT( timerquit()  ) );


    receivetimer->start(111);

    sendtimer->start( 121 );
ercomax_=6;
    erco_=ercomax_;



    connect( quitButton, SIGNAL( clicked() ), this, SLOT( slotclose() ) );
    connect( quitbothbutton, SIGNAL( clicked() ), this, SLOT( slotcloseboth() ) );

    connect( ghattbutton, SIGNAL( clicked() ), this, SLOT( slotghattbut()  ) );

    connect( centerviebut, SIGNAL( clicked() ), this, SLOT( slotcenterviebut()  ) );
    connect( lghbut, SIGNAL( clicked() ), this, SLOT( slotlghbut()  ) );
    connect( sightbbut, SIGNAL( clicked() ), this, SLOT( slotsightbbut()  ) );
    connect( sghbut, SIGNAL( clicked() ), this, SLOT( slotsghbut()  ) );
    connect( minewaitbut, SIGNAL( clicked() ), this, SLOT( slotminewaitbut()  ) );
    connect( spixubut , SIGNAL( clicked() ), this, SLOT( slotspixubut()  ) );
    connect( brakebut , SIGNAL( clicked() ), this, SLOT( slotbrakebut()  ) );
    connect( minecollectbut, SIGNAL( clicked() ), this, SLOT( slotminecollectbut()  ) );
    connect( splonbut , SIGNAL( clicked() ), this, SLOT( slotsplonbut()  ) );
    connect( safetyonbut, SIGNAL( clicked() ), this, SLOT( slotsafetyonbut()  ) );
    connect( ksuuntvhbut, SIGNAL( clicked() ), this, SLOT( slotksuuntvhbut()  ) );
    connect( asuuntvhbut, SIGNAL( clicked() ), this, SLOT( slotasuuntvhbut()  ) );
    connect( lsuuntvhbut, SIGNAL( clicked() ), this, SLOT( slotlsuuntvhbut()  ) );
    connect( miskohbut , SIGNAL( clicked() ), this, SLOT( slotmiskohbut()  ) );
    connect( mstbut, SIGNAL( clicked() ), this, SLOT( slotmstbut()  ) );
    connect( msmibut , SIGNAL( clicked() ), this, SLOT( slotmsmibut()  ) );
    connect( hudbut, SIGNAL( clicked() ), this, SLOT( slothudbut()  ) );
    connect( asthudbut, SIGNAL( clicked() ), this, SLOT( slotasthudbut()  ) );
    connect( isohudbut , SIGNAL( clicked() ), this, SLOT( slotisohudbut()  ) );
    connect( helptextonbut , SIGNAL( clicked() ), this, SLOT( slothelptextonbut()  ) );
    connect( shortmesonbut, SIGNAL( clicked() ), this, SLOT( slotshortmesonbut()  ) );

    connect(freelobut, SIGNAL( clicked() ), this, SLOT(slotfreelobut()  ) );
    connect(      sanglebut, SIGNAL( clicked() ), this, SLOT(slotsanglebut()  ) );
    connect(      fullscbut, SIGNAL( clicked() ), this, SLOT(slotfullscbut()  ) );
    connect(      edgecebut, SIGNAL( clicked() ), this, SLOT(slotedgecebut()  ) );
    connect(      ympybut, SIGNAL( clicked() ), this, SLOT(slotympybut()  ) );

    connect(   pausebut, SIGNAL( clicked() ), this, SLOT(slotpausebut()  ) );
    connect(        newgamebut, SIGNAL( clicked() ), this, SLOT(slotnewgamebut()  ) );
    connect(           newshipbut, SIGNAL( clicked() ), this, SLOT(slotnewshipbut()  ) );
    connect(           zoom_plusbut, SIGNAL( clicked() ), this, SLOT(slotzoom_plusbut()  ) );
    connect(           zoom_minusbut,  SIGNAL( clicked() ), this, SLOT(slotzoom_minusbut()  ) );
    connect(          reloadconfbut,  SIGNAL( clicked() ), this, SLOT(slotreloadconfbut()  ) );
    connect(           minebut,  SIGNAL( clicked() ), this, SLOT(slotminebut()  ) );
    connect(            detonbut,  SIGNAL( clicked() ), this, SLOT(slotdetonbut  ()  ) );
    connect(       clearbbut, SIGNAL( clicked() ), this, SLOT(slotclearbbut()  ) );
    connect(            ppicintbut,  SIGNAL( clicked() ), this, SLOT(slotppicintbut()  ) );
    connect(            thrustbut,  SIGNAL( clicked() ), this, SLOT(slotthrustbut()  ) );
    connect(          slowthrustbut, SIGNAL( clicked() ), this, SLOT(slotslowthrustbut()  ) );

    connect( minelaybut,  SIGNAL( clicked() ), this, SLOT( slotminelay()  )  );
    connect( minevisiblebut,  SIGNAL( clicked() ), this, SLOT( slotminevisible()  )  );
    connect(        bervisiblebut,  SIGNAL( clicked() ), this, SLOT( slotbervisible()  )  );
    connect(   enervisiblebut,  SIGNAL( clicked() ), this, SLOT( slotenervisible()  )  );
    connect(        boxvisiblebut,  SIGNAL( clicked() ), this, SLOT( slotboxvisible()  )  );
    connect(        explvisiblebut,  SIGNAL( clicked() ), this, SLOT( slotexplvisible()  )  );
    connect(        bercolbut,  SIGNAL( clicked() ), this, SLOT( slotbercol()  )  );
    connect(        enercolbut,  SIGNAL( clicked() ), this, SLOT( slotenercol()  )  );
    connect(         boxcolbut ,  SIGNAL( clicked() ), this, SLOT( slotboxcol()  )  );


    connect(insocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(insocket, SIGNAL( readyRead() ), this, SLOT( timb( )  )  );

    connect(insocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(displayError(QLocalSocket::LocalSocketError)));

    //    connect(ulospis, SIGNAL(bytesWritten(qint64)  )  , this, SLOT(readFortune()  ) );
    //  connect(ulospis, SIGNAL(readyRead()  )  , this, SLOT(readFortune()  ) );

    connect(outsocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(displayError(QLocalSocket::LocalSocketError)));


    QGridLayout *mainLayout = new QGridLayout;
    //  mainLayout->addWidget( statusLabel,  0, 2);
    mainLayout->addWidget( nopkyl,      1, 6 );
    mainLayout->addWidget( enerlabel,   2, 6 );

    mainLayout->addWidget( hcmodelab,    3, 6 );
    mainLayout->addWidget( ghinvlab,     4, 6 );

    mainLayout->addWidget( closelab,      5, 6 );
    mainLayout->addWidget( closestlab,    6, 6 );
    mainLayout->addWidget( spottednumlab_,   7,6  );
    mainLayout->addWidget( spotted_lios_lab_,8,6 );
    mainLayout->addWidget( spottedby_lab_,   9,6  );
    mainLayout->addWidget( zoomlab_, 10, 6 );

    mainLayout->addWidget( pacxlab_,11,6 );
    mainLayout->addWidget( pacylab_, 12,6 );

    mainLayout->addWidget( reasonlab,     1, 7 );
    mainLayout->addWidget( pacliveslab,   2, 7 );
    mainLayout->addWidget( nofalab,       3, 7 );
    mainLayout->addWidget( traillab,      4, 7 );
    mainLayout->addWidget( ghost_modelab,  5, 7 );
    mainLayout->addWidget( unpickedberlab, 6, 7 );
    mainLayout->addWidget( berlab, 7, 7 );
    mainLayout->addWidget(  missileslab,   8, 7 );
    mainLayout->addWidget(  mineslab,     9, 7 );
    mainLayout->addWidget( tecounter_lab_, 10, 7 );
    mainLayout->addWidget( setcou_lab_, 11,7 );
    mainLayout->addWidget( finitefuellab, 12,7 );
    mainLayout->addWidget( velocityalab_, 13,7);
    mainLayout->addWidget(   velocityblab_, 14,7);

    mainLayout->addWidget(  minesoutlab,  1, 8 );
    mainLayout->addWidget( spinghostslab,  2, 8 );
    mainLayout->addWidget( normalghostslab,3, 8 );
    mainLayout->addWidget( ghostcountlab,4, 8 );
    mainLayout->addWidget( fpslab,       5, 8 );
    mainLayout->addWidget( shortmsglab,  6, 8 );
    mainLayout->addWidget( spottedlab,  7, 8 );



    mainLayout->addWidget( buttonBoxa, 4, 9 );



    mainLayout->addWidget(  fuelwarnlab, 8,8 );
    mainLayout->addWidget(          minewarnlab, 9,8 );
    mainLayout->addWidget(         misswarnlab, 10,8 );
    mainLayout->addWidget( speedwarnlab, 11,8 );

    mainLayout->addWidget( buttonBox1, 1, 1,11,1 );
    mainLayout->addWidget( buttonBox2, 1, 2,11,1 );
    mainLayout->addWidget( buttonBox3, 1, 3,11,1  );
    mainLayout->addWidget( buttonBox4, 1, 4,11,1  );
    mainLayout->addWidget( buttonBox5, 1, 5,11,1  );

    buttonBox1->setCenterButtons( 1 );

    setLayout(mainLayout);

    setWindowTitle(tr("P-PFsCUd display & control"));
    mainLayout->setRowMinimumHeight( 4, 30  );
    mainLayout->setColumnMinimumWidth( 1, 30  );

    mainLayout->	setRowStretch(4, 30);
    mainLayout->	setColumnStretch(4, 30);

    mainLayout->setVerticalSpacing( 30 );

    //mainLayout->SetMinimumSize(20);

    cout << " cons2 " << endl;

}

void Client::laheta()
{
    outsocket->connectToServer( inservername_ );
    //outsocket->seek(0);
    uint iteru;
    QByteArray outqba;
    for( iteru=0 ; iteru<bointsli_.size() ; iteru++ )
    {

        outqba.push_back( qbachar( bointsli_.at( iteru ).bb, bointsli_.at( iteru ).sw ) );
        bointsli_.at( iteru).sw=0;

    }
    outsocket->write( outqba );
    outsocket->flush();
    if( bointsli_.at( closeboth_pla_ ).bb ==1 )
    {
        cout << endl << endl << "  quitboth  " << endl << endl;
        outsocket->disconnectFromServer();
        insocket->disconnectFromServer();

        exit(0);

    }
}


void Client::requestNewFortune()
{

    blockSize = 0;
    insocket->abort();
    outsocket->abort();
    insocket->connectToServer( outservername_ );



}
void Client::readFortune()
{

    QDataStream in( insocket );
  //  in.setVersion( QDataStream::Qt_4_8 );
    string sana("abcd"), sn;
    QString qsana, qsn;
    qsn=insocket->fullServerName();
    sn=qsn.toStdString();

   // in.device()->seek(0);

   // insocket->seek(0);
    qar_.clear();
    qar_=insocket->readAll();



    int ite;
    sana.clear();
    sana=qar_.data();
    if( qar_.size()>=qbamax_ /*+bointsli_.size()*/ )
    {

        fuel_= qbatofloat( ener_pla_, qar_ );
        speed_= qbatofloat( speed_pla_, qar_ );

        mines_=qbatoint( mines_pla_, qar_ );
        minesout_=qbatoint( mines_out_pla_, qar_ );
        missiles_=qbatoint( miss_pla_, qar_ );


        norghostcount_=qbatoint( norghostcount_pla_, qar_ );
        spinghostcount_=qbatoint( spinghostcount_pla_, qar_ );
        ghostcount_=qbatoint( ghostcount_pla_, qar_ );
        ghost_mode_=qbatoint( ghost_mode_pla_, qar_ );
        ber_=qbatoint( ber_pla_, qar_ );
        unber_=qbatoint( unber_pla_, qar_ );
        tec_=qbatoint( tec_pla_, qar_ );
        setcou_=qbatoint( setcou_pla_, qar_ );

        traffic_collision_velocity_= qbatofloat( traffic_collision_velocity_pla_, qar_ );
        speed_limiterf_= qbatofloat( speed_limiterf_pla_, qar_ );
        zoom_ = qbatofloat( zoom_pla_, qar_ );
        pac1x1_=qbatofloat( pac1x1_pla_, qar_ );
        pac1y1_= qbatofloat( pac1y1_pla_, qar_ );
        velocitya_= qbatofloat( velocitya_pla_, qar_ );
        velocityb_= qbatofloat( velocityb_pla_, qar_ );

        spottednum_=qbatoint( spottednum_pla_, qar_ );
        spotted_lios_=qbatoint( spotted_lios_pla_, qar_ );
        spottedby_=qbatoint( spottedby_pla_, qar_ );

        closest_=qbatofloat( closest_pla_, qar_ );
        reason_=qbatoint( reason_pla_, qar_ );

        fps_=qbatofloat( fps_pla_, qar_  );



        int ncve=bointsli_.size()*2;
        uint itebe=0;
        for( ite=0 ; ite<ncve ; ite+=2 )
        {

            if( ite+1 < qar_.size() )
            {
                if( itebe>=bointsli_.size() )
                {
                    cout << endl << " readf: error1  " << itebe << "  size=" << bointsli_.size() << endl;
                }

                if( qar_.at( ite+1 ) or bointsli_.at( itebe ).init==0  or bointsli_.at( itebe ).sw==0 )
                {
                    bointsli_.at( itebe ).bb= qar_.at( ite );

                }
            }
            else
            {
                cout << endl << " readf: error2  " << ite+1 << "  size=" << qar_.size() << endl;
            }
            bointsli_.at( itebe ).init=1;
            itebe++;
        }






        string sfuel, svel, smines, smis;
        stringstream fuelss, velss, miness, misss;

        fuelss << fuel_;
        fuelss >> sfuel;

        velss.precision(3);
        velss << speed_;
        velss >> svel;



        labtextnum( "spe", prec( speed_,0.01  ), nopkyl );
        labtextnum( "fuel", fuel_, enerlabel );



        labtextnum( "closest", closest_, closestlab );

        labtextnum( "spot", spottednum_, spottednumlab_ );
        labtextnum( "spotls", spotted_lios_, spotted_lios_lab_ );
        labtextnum( "spottedby", spottedby_, spottedby_lab_ );
        labtextnum( "norghostcount", norghostcount_, normalghostslab );
        labtextnum( "spinghostcount", spinghostcount_, spinghostslab );
        labtextnum( "ghostcount", ghostcount_, ghostcountlab );
        labtextnum( "ghost_mode", ghost_mode_, ghost_modelab );
        labtextnum( "ber", ber_, berlab );
        labtextnum( "unber", unber_, unpickedberlab );
        labtextnum( "tec",  tec_, tecounter_lab_ );
        labtextnum( "setcou", setcou_, setcou_lab_ );
        labtextnum( "mines", mines_, mineslab );
        labtextnum( "minesout", minesout_, minesoutlab );
        labtextnum( "reason", reason_, reasonlab );
        labtextnum( "missiles", missiles_, missileslab );

        labtextnum( "shortmsg", shortmsg_, shortmsglab );

        labtextnum( "zoom", prec( zoom_, 0.01 ), zoomlab_  );
        labtextnum( "fps", fps_,  fpslab );

        labtextnum( "vela", velocitya_, velocityalab_  );
        labtextnum( "velb" ,  velocityb_  ,  velocityblab_ );
        labtextnum( "pac-x",  pac1x1_ , pacxlab_ );
        labtextnum("pac-y", pac1y1_, pacylab_ );




        labswi( qbarswi( close_pla_, qar_),  closelab );

        labswi2(  qbarswi( ghinv_pla_, qar_ ), ghinvlab );

        labswi2( qbarswi( hcmode_pla_, qar_ ), hcmodelab  );

        bool speedw, fuelw, minewarn, missw;
        if( speed_> traffic_collision_velocity_ )
            speedw=1;
        else speedw=0;

        if( fuel_<400)
            fuelw=1;
        else
            fuelw=0;

        if( missiles_<20)
            missw=1;
        else missw=0;


        if( mines_<10)
            minewarn=1;
        else minewarn=0;

        labswi( speedw, speedwarnlab );
        labswi( fuelw, fuelwarnlab );
        labswi( missw, misswarnlab );
        labswi( minewarn, minewarnlab );

        labswi2( qbarswi( finitefuel_pla_, qar_ ), finitefuellab );

        labswi2( qbarswi( paclives_pla_, qar_ ), pacliveslab  );
        labswi2( qbarswi( nofa_pla_, qar_ ), nofalab  );
        labswi2( qbarswi( trail_pla_, qar_ ), traillab  );



        if( spottedby_>0 )
        {
            //   spottedt_=100;
            spot_tec_=tec_;
        }
        else
        {
            // spottedt_--;

        }
        if(   spot_tec_+200 > tec_    )
        {
            if( spot_tec_+2>tec_ )
            {
                labswi( 1, spottedlab  );
            }
            else
            {
                labswi( 2, spottedlab  );


            }

        }
        else
        {
            labswi( 0, spottedlab  );

        }



        buttonswi( qbarswi( explvisible_pla_, qar_ ), explvisiblebut );

        minecollectbut->setAutoFillBackground(true);



        buttonsel2( qbarswi( ghatt_pla_, qar_ ), ghattbutton );
     //   buttonswi( qbarswi( centervie_pla_, qar_ ), centerviebut );
        buttonswi( qbarswi( minecollect_pla_, qar_ ), minecollectbut );

     //   buttonswi( qbarswi( sightb_pla_, qar_ ), sightbbut) ;

        buttonswi( qbarswi( minewait_pla_, qar_ ), minewaitbut ) ;
      //  buttonswi( qbarswi( spixu_pla_, qar_ ),spixubut ) ;


        buttonsel2( qbarswi( brake_pla_ , qar_ ), brakebut );


        buttonswi2( speed_limiterf_, speed_, qbarswi( splon_pla_, qar_ ),splonbut ) ;


        buttonswi( qbarswi(  safetyon_pla_, qar_ ),safetyonbut );
        buttonswi( qbarswi(  ksuuntvh_pla_, qar_ ),ksuuntvhbut );
        buttonswi( qbarswi(   asuuntvh_pla_, qar_ ),asuuntvhbut );
        buttonswi( qbarswi(  lsuuntvh_pla_, qar_ ),lsuuntvhbut );
        buttonswi( qbarswi(  miskoh_pla_ , qar_ ),miskohbut );
        buttonswi( qbarswi(   mst_pla_ , qar_ ),mstbut );
        buttonswi( qbarswi(   msmi_pla_ , qar_ ),msmibut );
        buttonswi( qbarswi(   hud_pla_, qar_ ),hudbut );
        buttonswi( qbarswi(   asthud_pla_, qar_ ),asthudbut );
        buttonswi( qbarswi(   isohud_pla_ , qar_ ),isohudbut );
        buttonswi( qbarswi(   helptexton_pla_, qar_ ),helptextonbut ) ;
        buttonswi( qbarswi(   shortmeson_pla_, qar_ ),shortmesonbut );
        buttonswi( qbarswi(   freelo_pla_, qar_ ),freelobut ) ;
        buttonswi( qbarswi(   sangle_pla_, qar_ ), sanglebut );
        buttonswi( qbarswi(   fullsc_pla_ , qar_ ),fullscbut );
        buttonsel2( qbarswi(   edgece_pla_, qar_ ), edgecebut );
        buttonsel2( qbarswi(  minelay_pla_, qar_ ), minelaybut );

        buttonswi( qbarswi( pause_pla_ , qar_ ),   pausebut );
        buttonswi( qbarswi(  newgame_pla_ ,  qar_ ),      newgamebut );
        buttonswi( qbarswi( newship_pla_  ,   qar_ ),        newshipbut );
        buttonswi( qbarswi( zoom_plus_pla_ ,  qar_ ),          zoom_plusbut );
        buttonswi( qbarswi( zoom_minus_pla_ ,  qar_ ),          zoom_minusbut );
        buttonswi( qbarswi( reloadconf_pla_ , qar_ ),          reloadconfbut );
        buttonsel2( qbarswi( mine_pla_    ,  qar_ ),       minebut );
        buttonsel2( qbarswi( deton_pla_   ,  qar_ ),         detonbut );
        buttonswi( qbarswi(  clearb_pla_  ,  qar_ ),     clearbbut );
        buttonswi( qbarswi(  ppicint_pla_   ,  qar_ ),         ppicintbut );
        buttonswi( qbarswi(   thrust_pla_   ,  qar_ ),        thrustbut );

        buttonswi( qbarswi(minevisible_pla_   ,  qar_ ), minevisiblebut);
        buttonswi( qbarswi( bervisible_pla_     ,  qar_ ),     bervisiblebut);
        buttonswi( qbarswi( enervisible_pla_    ,  qar_ ),  enervisiblebut);
        buttonswi( qbarswi( boxvisible_pla_   ,  qar_ ),      boxvisiblebut);
        buttonswi( qbarswi( bercol_pla_       ,  qar_ ), bercolbut);
        buttonswi( qbarswi(     enercol_pla_   ,  qar_ ),    enercolbut);
        buttonswi( qbarswi(    boxcol_pla_     ,  qar_ ),   boxcolbut);


        int ympy_z=qbarswi( ympy_pla_, qar_ );
        buttonsel( qbarswi( ympy_pla_, qar_ ), /*3,*/ ympybut );
        if( ympy_z==0 )
            ympybut->setText( "velmet  " );

        if( ympy_z==1 )
            ympybut->setText( "velmet a" );

        if( ympy_z==2 )
            ympybut->setText( "velmet b" );

        buttonswi( qbarswi(  slowthrust_pla_, qar_ ), slowthrustbut );

    }

    if( coute_%30==0 )
    {
        clearfocuses();
    }

    coute_++;
}

void Client::labswi( int swi, QLabel *lab  )
{

    if( swi==1 )
    {
        lab->setPalette( pal_warning_ );
    }
    if(swi==0 )
    {

        lab->setPalette( pal_normal_ );


    }
    if( swi==2 )
    {
        lab->setPalette( pal_warning2_ );
    }

    // cout << " labswi " << endl;

}
void Client::labswi2( int swi, QLabel *lab  )
{

    if( swi==1 )
    {
        lab->setPalette( pal_on_ );
    }
    if(swi==0 )
    {

        lab->setPalette( pal_off_ );


    }
    if( swi==2 )
    {
        lab->setPalette( pal_warning2_ );
    }


}

void Client::labtextnum( QString tex,  double num, QLabel *lab )
{
    tex+=QString( " %1 ").arg( num );

    lab->setFixedWidth( 300 );
    lab->setText( tex  );
    lab->setPalette( pal_normal2_ );
}


void Client::buttonswi( bool swi, QPushButton *button  )
{

    if( swi )
    {

        button->setPalette( pal_on_ );

    }
    else
    {

        button->setPalette( pal_off_ );


    }

}

void Client::buttonswi2( float aaa, float bbb, bool swi, QPushButton *button  )
{


    if( swi )
    {
        if(bbb<aaa-0.6 )
        {
            button->setPalette( pal_on_ );
        }
        else
        {
            if( bbb>=aaa )
            {
                button->setPalette( pal_warning_ );
            }
            else
            {
                button->setPalette( pal_warning2_ );
            }

        }
    }
    else
    {

        button->setPalette( pal_off_ );


    }

}


void Client::buttonsel( int sel,  QPushButton *button  )
{
    if( sel>0 )
    {
        button->setPalette( pal_on_ );
    }
    else
    {
        button->setPalette( pal_off_ );
    }


}

void Client::buttonsel2( int sel, QPushButton *button )
{
    if( sel==1 )
    {
        button->setPalette( pal_on_ );
    }
    if( sel==0 )
    {
        button->setPalette( pal_off_ );

    }
    if( sel==2 )
    {
        button->setPalette( pal_unswit_ );
    }

    if( sel==3 )
    {
        button->setPalette( pal_warning2_ );

    }


}

void Client::timerquit( )
{

    cout << " " << mestimer_ << flush;
    mestimer_--;
    if( mestimer_< 1  )
    {
        cout << endl <<  endl << " timerquit " << endl << endl ;
        outsocket->disconnectFromServer();
        insocket->disconnectFromServer();
        exit(0);
    }
    if( erco_<0 )
    {
        cout << endl <<  endl << " timerquit vl " << endl << endl ;
        outsocket->disconnectFromServer();
        insocket->disconnectFromServer();
        exit(0);
    }

    QString tratex=*trx_;
    tratex+=QString::number( mestimer_ );
    tratex+="  clicks: ";
    tratex+=QString::number( erco_ );

    mesbo_->setText( tratex );


}
void Client::timb()
{
    rea_=1;
    messagetimer->stop(  );
    erco_=ercomax_;
    mestimer_=25;
}


void Client::displayError( QLocalSocket::LocalSocketError socketError )
{
    if( erco_<0 )
    {
        cout << " vaat " << endl;
        outsocket->disconnectFromServer();
        insocket->disconnectFromServer();
        exit(0);
    }
    mesbo_=new QMessageBox( this );

    if( erco_>=ercomax_-2 )
    {
        messagetimer->start( 1000 );
        mestimer_=29;
        rea_=0;
    }
    if( mestimer_< 1 or erco_<0 )
    {
        cout << endl << " mt  " << mestimer_ << endl << "   vl    " << erco_ << endl;
        outsocket->disconnectFromServer();
        insocket->disconnectFromServer();
        exit(0);
    }
    *trx_=" error -- ";

    switch ( socketError ) {
    case

    QLocalSocket::ServerNotFoundError:

        erco_--;
        *trx_="The other program was not found. Maybe check the "
              "host name and port settings. ";
        mesbo_->exec();

        break;
    case QLocalSocket::ConnectionRefusedError:

        erco_--;
        /* QMessageBox::information( this, tr("Client" ),
                                 tr("The connection was refused by the peer. "
                                    "Make sure it is running, "
                                    "and maybe check that the host name and port "
                           "settings are correct."));
                           */
        *trx_="The connection was refused by the peer. "
              "Make sure it is running, "
              "and maybe check that the host name and port "
              "settings are correct.";

        break;
    case QLocalSocket::PeerClosedError:
        //  erco_--;
        //   mesbo_->exec();

        break;
    default:
        /*        QMessageBox::information(this, tr("Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(insocket->errorString()));*/
        *trx_=QString("The following error occurred: %1.").arg(insocket->errorString());
        //    mesbo_->exec();

        //    erco_--;

    }

}

void Client::enableGetFortuneButton()
{
    cout << " enableGetFortuneButton 1 " << endl;

}


void Client::slotghattbut()
{
    fboi( ghatt_pla_ ) ;

}

void Client::slotcenterviebut()
{
    fboi(  centervie_pla_  );
}

void Client::slotlghbut()
{
    fboi( 2 );
}
void Client::slotsightbbut()
{
    fboi(  sightb_pla_   );
}

void Client::slotsghbut()
{
    fboi(  1  );
}
void Client::slotminewaitbut()
{
    fboi(  minewait_pla_  );
}
void Client::slotspixubut()
{
    fboi(  spixu_pla_  );
}
void Client::slotbrakebut()
{
    fboi(  brake_pla_  );
}
void Client::slotminecollectbut()
{
    fboi(  minecollect_pla_  );
}

void Client::slotsplonbut ()
{
    fboi(  splon_pla_  );
}
void Client::slotsafetyonbut()
{
    fboi(  safetyon_pla_  );
}
void Client::slotksuuntvhbut()
{
    fboi(  ksuuntvh_pla_  );
}
void Client::slotasuuntvhbut ()
{
    fboi(  asuuntvh_pla_  );
}
void Client::slotlsuuntvhbut()
{
    fboi(  lsuuntvh_pla_  );
}
void Client::slotmiskohbut ()
{
    fboi(  miskoh_pla_  );
}
void Client::slotmstbut ()
{
    fboi(  mst_pla_  );
}
void Client::slotmsmibut ()
{
    fboi(  msmi_pla_  );
}
void Client::slothudbut()
{
    fboi(  hud_pla_  );
}
void Client::slotasthudbut()
{
    fboi(  asthud_pla_  );
}
void Client::slotisohudbut()
{
    fboi(  isohud_pla_  );
}
void Client::slothelptextonbut ()
{
    fboi(  helptexton_pla_   );
}
void Client::slotshortmesonbut()
{
    fboi(  shortmeson_pla_  );
}


void Client::slotfreelobut()
{
    fboi(  freelo_pla_  );
}

void Client::slotsanglebut()
{
    fboi(  sangle_pla_  );
}

void Client::slotfullscbut()
{
    fboi(  fullsc_pla_  );
}

void Client::slotedgecebut ()
{
    fboi(  edgece_pla_  );
}
void Client::slotympybut()
{

    seboi(  ympy_pla_ , 3 );
}

void  Client::slotpausebut()
{
    fboi(  pause_pla_  );
}
void  Client::slotnewgamebut()
{
    fboi(  newgame_pla_  );
}
void  Client::slotnewshipbut()
{
    fboi(  newship_pla_  );
}
void Client:: slotzoom_plusbut()
{
    fboi(  zoom_plus_pla_  );
}
void  Client::slotzoom_minusbut()
{
    fboi(  zoom_minus_pla_  );
}
void  Client::slotreloadconfbut()
{
    fboi(  reloadconf_pla_  );
}
void  Client::slotminebut()
{
    fboi(  mine_pla_  );
}
void  Client::slotdetonbut()
{
    fboi(  deton_pla_  );
}
void  Client::slotclearbbut()
{
    fboi(  clearb_pla_  );
}
void Client:: slotppicintbut()
{

    seboi(  ppicint_pla_ , 3 );
}
void  Client::slotthrustbut()
{
   if( fboi(  thrust_pla_  )==1  )
   {
     if( bointsli_.at( slowthrust_pla_ ).bb==1 )
     {
     fboi(  slowthrust_pla_  );
     }
   }
}
void  Client::slotslowthrustbut()
{
    if( fboi(  slowthrust_pla_  )==1  )
    {
        if( bointsli_.at( thrust_pla_ ).bb==1 )
        {
         fboi(  thrust_pla_  ) ;
        }
    }

}
void  Client::slotminelay()
{
    fboi( minelay_pla_ );
}

void Client::slotminevisible()
{
    fboi(  minevisible_pla_  );
}
void  Client::slotbervisible()
{
    fboi(  bervisible_pla_  );
}
void Client::slotenervisible()
{
    fboi(  enervisible_pla_  );
}
void Client::slotboxvisible()
{
    fboi(  boxvisible_pla_  );
}
void  Client::slotexplvisible()
{
    fboi(  explvisible_pla_  );
}

void Client::slotbercol()
{
    fboi(  bercol_pla_  );
}
void Client::slotenercol()
{
    fboi(  enercol_pla_  );
}
void Client::slotboxcol()
{
    fboi(  boxcol_pla_  );
}
void Client::slotclose()
{
    cout << endl << endl << " close " << endl << endl ;
    outsocket->disconnectFromServer();
    insocket->disconnectFromServer();
    exit(0);
}

void Client::slotcloseboth()
{
    fboi(  closeboth_pla_  );

}
void Client::clearfocuses(   )
{
    ghattbutton ->clearFocus();
    centerviebut->clearFocus();
    lghbut->clearFocus();
    sightbbut->clearFocus();
    sghbut->clearFocus();
minewaitbut->clearFocus();


    spixubut->clearFocus();
    brakebut->clearFocus();
    minecollectbut->clearFocus();
    splonbut->clearFocus();
    safetyonbut->clearFocus();
    ksuuntvhbut->clearFocus();
    asuuntvhbut->clearFocus();
    lsuuntvhbut->clearFocus();
    miskohbut->clearFocus();
    mstbut->clearFocus();
    msmibut->clearFocus();
    hudbut->clearFocus();
    asthudbut->clearFocus();
    isohudbut->clearFocus();
    helptextonbut->clearFocus();
    shortmesonbut   ->clearFocus();

    freelobut->clearFocus();
    sanglebut->clearFocus();
    fullscbut->clearFocus();
    edgecebut->clearFocus();
    ympybut->clearFocus();

    pausebut->clearFocus();
    newgamebut->clearFocus();
    newshipbut->clearFocus();
    zoom_plusbut->clearFocus();
    zoom_minusbut->clearFocus();
    reloadconfbut->clearFocus();
    minebut->clearFocus();
    detonbut->clearFocus();
    clearbbut->clearFocus();
    ppicintbut->clearFocus();
    thrustbut->clearFocus();
    slowthrustbut->clearFocus();
    minelaybut->clearFocus();
    explvisiblebut->clearFocus();

    bervisiblebut->clearFocus();
        enervisiblebut->clearFocus();
            boxvisiblebut->clearFocus();
bercolbut->clearFocus();
            enercolbut->clearFocus();
            boxcolbut->clearFocus();
minevisiblebut->clearFocus();


}
