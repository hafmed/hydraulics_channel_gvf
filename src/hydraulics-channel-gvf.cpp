//le 3-4-2020 - 5-9-2020
//Newton-Raphson method
//Paine (1992) developed an algorithm for GVF profile computations (for prismatic
//channels) using Manning formula of flow resistance. Newton-Raphson technique was
//used for guaranteed convergence of the algorithm. Standard step functions f(Y) and f'(Y)
//developed by Paine were tested for numerical convergence under a wide variety of flow
//conditions in subcritical, critical, horizontal, and adverse flow regimes. The Newton-
//Raphson technique has consistently converged.
//However, there are two basic problems associated with Paine's algorithm:
//(1) Manning's equation is accurate in an intermediate range of roughness ratios: it
//predicts unrealistically low friction and high discharge for both deep smooth and
//shallow rough channels, for which the friction-factor formulation would be
//preferred (White, 1986).
//(2) Newton-Raphson method, as has already been established in the previous pages,
//is quite sensitive to the starting point and its rate of convergence is quite less.
//(3) The algorithm is not applicable to natural streams.

#include "hydraulics-channel-gvf.h"
#include "ui_hydraulics-channel-gvf.h"
#include <QDebug>
//#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

#include <math.h>
#include <fstream>

#include <stdlib.h>

#include<algorithm>
#include<vector>

#include <cmath>
#include <cstdlib>
#include "math.h"

#include <utility>  //declarations of unique_ptr
#include <iostream>
#include <memory>
using std::unique_ptr;
using namespace std;
#include <iomanip>

#include <constants.h>

hydraulics_channel_gvf::hydraulics_channel_gvf(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hydraulics_channel_gvf)
{
    ui->setupUi(this);
    /////ui->statusBar->showMessage("HAFIANE Mohamed (2020-2021) ; Ver: " APP_VERSION " ; Linux&Windows ; email : haftemp@gmail.com ; https://sites.google.com/site/courshaf"+
    /////                           tr("        ;          Sens d'écoulement : --------->"));
    setWindowTitle(tr("Courbes de remous (résolution numérique et intégration directe)"));
    //--------------------HAF 9-8-2021---------------------------
    QString fig_gvf_fr ="image: url(:/icons/GVF-Eqts-Fr.png);";
    /////QPixmap (":/icons/GVF-Eqts-Fr.png");
    QString fig_gvf_en = "image: url(:/icons/GVF-Eqts-En.png);";
    ////QPixmap (":/icons/GVF-Eqts-En.png");
    QString locale = QString(QLocale::system().name()).left(2);
    if (locale.length() < 2) locale = "en";
    if (locale!="fr")
    {
        ui->label_figGVF->setStyleSheet(fig_gvf_en);
    }else{
        ui->label_figGVF->setStyleSheet(fig_gvf_fr);
    }
    //------------------------HAF 25-7-2020----------------------
    ui->doubleSpinBox_y1->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_y1->setGroupSeparatorShown(false);
    ui->doubleSpinBox_y2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_y2->setGroupSeparatorShown(false);
    ui->doubleSpinBox_S0->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_S0->setGroupSeparatorShown(false);
    ui->doubleSpinBox_coefManning->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_coefManning->setGroupSeparatorShown(false);
    ui->doubleSpinBox_Q->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_Q->setGroupSeparatorShown(false);
    ui->doubleSpinBox_y0->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_y0->setGroupSeparatorShown(false);
    ui->doubleSpinBox_b->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_b->setGroupSeparatorShown(false);
    ui->doubleSpinBox_m->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_m->setGroupSeparatorShown(false);
    ui->doubleSpinBox_dx->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_dx->setGroupSeparatorShown(false);
    ui->doubleSpinBox_L->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_L->setGroupSeparatorShown(false);
    ui->doubleSpinBox_epsilon->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->doubleSpinBox_epsilon->setGroupSeparatorShown(false);
    //------------------------------------------------------------
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(9);

    connect(ui->pushButton_Calculer, SIGNAL(clicked()), this, SLOT(calcul_HAF()));

    connect(ui->radioButton_AngloSaxon, SIGNAL(toggled(bool)), this, SLOT(SI_unite_HAF()));
    connect(ui->pushButton_copy_table_in_Clipboard, SIGNAL(clicked()), this, SLOT(copy_table_in_Clipboard()));

    ui->radioButton_Bresse->setToolTip(tr("Méthode de Bresse est pour un canal rectangulaire très large!"));

    connect(ui->spinBox_nbrePts, SIGNAL(valueChanged(int)), this, SLOT(remplire_Colonne_Yinpt(int)));
    connect(ui->doubleSpinBox_y1, SIGNAL(valueChanged(double)), this, SLOT(remplire_Colonne_Yy1(double)));
    connect(ui->doubleSpinBox_y2, SIGNAL(valueChanged(double)), this, SLOT(remplire_Colonne_Yy2(double)));

    /////connect(ui->radioButton_NR, SIGNAL(toggled(bool)), this, SLOT(Sfmoy_NR_HAF()));

    connect(ui->radioButton_Bresse, SIGNAL(toggled(bool)), this, SLOT(desatif_noneed_Bresse_HAF(bool)));
    connect(ui->radioButton_DirectStep, SIGNAL(toggled(bool)), this, SLOT(desatif_noneed_DirectStep(bool)));
    connect(ui->comboBox_methode_calcul, SIGNAL(currentIndexChanged(int)), this, SLOT(desatif_L_HAF(int)));
#if defined(Q_OS_ANDROID)
    ui->pushButton_saveGraphe->hide();
#else
    ui->pushButton_saveGraphe->show();
    connect(ui->pushButton_saveGraphe, SIGNAL(clicked()), this, SLOT(saveGrapheToFile()));
#endif

    //pd.setWindowModality(Qt::WindowModal);
    pd.setWindowModality(Qt::ApplicationModal);
    pd.setLabelText(tr("Calcul en cours, Veuillez patienter!"));
    pd.setCancelButtonText(tr("Annuler"));
    pd.setFocus();
    pd.setAutoReset(true);
    pd.setEnabled(true);
    //---HAF-30-08-2020---
    connect(ui->radioButton_AngloSaxon, SIGNAL(toggled(bool)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_Q, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_S0, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_L, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_coefManning, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_b, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    connect(ui->doubleSpinBox_m, SIGNAL(valueChanged(double)), this, SLOT(Affichage_ycyn_HAF()));
    //--------------------
    ///-mettre à la fin tjrs
    ui->checkBox_useYi->hide();

    calcul_HAF();

    /////ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/figeqtdiffGVF.png);");

}

hydraulics_channel_gvf::~hydraulics_channel_gvf()
{
    delete ui;
    delete [] y2;
    delete [] xx;
    delete [] zz;
    delete [] error_truncation;

    delete [] x;
    delete [] y;
    delete [] dx;
}
#if !defined(Q_OS_ANDROID)
void hydraulics_channel_gvf::saveGrapheToFile()
{
    QString fileName;
    int height=750, width=350;
    bool ok;
    width = QInputDialog::getInt(this, tr("hydraulics-channel-gvf"),
                                 tr("Choisir la hauteur de l'image :"), 350, 210, 500, 1, &ok);
    if (ok)
        height = QInputDialog::getInt(this, tr("hydraulics-channel-gvf"),
                                      tr("Choisir la largeur de l'image:"), 750, 210, 850, 1, &ok);
    QString file_name, extension;
    QString pdf_filter = tr("Portable Document Format (*.pdf)");
    QString png_filter = tr("Portable Network Graphics (*.png)");
    QString bmp_filter = tr("Windows Bitmap (*.bmp)");
    QString jpeg_filter = tr("JPEG File Interchange Format (*.jpeg *.jpg)");
    QString filter = QString("%1;;%2;;%3;;%4")
            .arg(png_filter)
            .arg(bmp_filter)
            .arg(jpeg_filter)
            .arg(pdf_filter);
    if (ok)
        file_name = QFileDialog::getSaveFileName(this, tr("hydraulics-channel-gvf : Sauvegarder le graphique sous ..."),
                                                 "", filter, &extension);
    if (file_name.length() > 0) {
        if (extension.compare(pdf_filter) == 0) {
            ui->customPlot->savePdf(file_name,height,width,QCP::epNoCosmetic,"hydraulics-channel-gvf","hydraulics-channel-gvf");
        } else if (extension.compare(png_filter) == 0) {
            ui->customPlot->savePng(file_name,height,width,1,-1);
        } else if (extension.compare(bmp_filter) == 0) {
            ui->customPlot->saveBmp(file_name,height,width,1,-1);
        } else if (extension.compare(jpeg_filter) == 0) {
            ui->customPlot->saveJpg(file_name,height,width,1,-1);
        }
    }
}
#endif
void hydraulics_channel_gvf::calcul_HAF(){
    //-----au debut tjrs-------------------------
    ui->label_Type_CR->setText("");
    //ui->tabWidget->setCurrentIndex(1);//12-7-2020 Win10
    ui->customPlot->clearGraphs();
    memset(y2, 0, 1000000*sizeof(double));
    for( int g=0; g<ui->customPlot->graphCount(); g++ )
    {
        ui->customPlot->graph(g)->data().clear();
    }
    ui->customPlot->replot();
    pd.reset();
    //pd.show(); //15-6-2020 ubuntu
    //--------------------------------------------
    if(ui->comboBox_methode_calcul->currentIndex()==0){
        ui->checkBox_useYi->setChecked(false);
    }

    if(ui->comboBox_methode_calcul->currentIndex()==0 && ui->comboBox_Methods->currentIndex()==0){
        methode_NR();
    }
    if(ui->comboBox_methode_calcul->currentIndex()==0 && ui->comboBox_Methods->currentIndex()==1){
        methode_RK4();
    }
    if(ui->comboBox_methode_calcul->currentIndex()==0 && ui->comboBox_Methods->currentIndex()==2){
        methode_KM();
    }
    if(ui->comboBox_methode_calcul->currentIndex()==0 && ui->comboBox_Methods->currentIndex()==3){
        methode_Trap();
    }
    if(ui->comboBox_methode_calcul->currentIndex()==1){
        if(ui->doubleSpinBox_S0->value()<=0 && ui->radioButton_Bresse->isChecked()){
            pd.close();
            QMessageBox::critical(this,tr("Erreur"),
                                  tr("La méthode de Bresse ne peut être utilisée que pour une pente de fond du canal So>0."));
            return ;
        }
        if (ui->radioButton_Bresse->isChecked()){ methode_Bresse();}
        if (ui->radioButton_DirectStep->isChecked()){ methode_DirectStep();}
    }
    ///---mettre à la fin tjrs
    if(ui->doubleSpinBox_S0->value()<=0){
        ui->label_yn->hide();
        ui->label_unite_yn->hide();
        if(ui->customPlot->graphCount()!=0) ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->replot();
    }else{
        ui->label_yn->show();
        ui->label_unite_yn->show();
    }
    // HAF 25-8-2020
//#if !defined(Q_OS_ANDROID)// HAF 25-7-2022
//    int width = (ui->tableWidget->model()->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
//    for(int column = 0; column < ui->tableWidget->model()->columnCount(); column++)
//        width = width + ui->tableWidget->columnWidth(column);
//    ui->tableWidget->setMinimumWidth(width);
//#endif
    /////-HAF 31-7-2022-----
    ui->tableWidget->resizeColumnsToContents();
    /////-------------------
    ui->stackedWidget_plot_imageEqts->setCurrentIndex(0);
    //----HAF 22-9-2020-----------
    ui->customPlot->yAxis->setRange(0, ymaxgraphe+0.15*fabs(ymaxgraphe));
    ui->customPlot->replot();
    //---------------------------
}
void hydraulics_channel_gvf::methode_Trap(){

    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double Cm;
    double g;
    double y=ui->doubleSpinBox_y0->value();
    double B=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();
    double z=0;
    double x=0;
    double stepdist=ui->doubleSpinBox_dx->value();
    double totaldist=ui->doubleSpinBox_L->value();

    if (totaldist<stepdist) {
        ui->doubleSpinBox_dx->setValue(totaldist/10);
    }

    if (abs(totaldist/stepdist) > 1000000 ){
        pd.close();
        QMessageBox::critical(this,tr("Erreur"),
                              tr("Impossible de continuer, vous avez dépasser le nombre max de points de calcul (1000000), diminuer la longueur du canal ou augmenter dx!"));
        //cout<< "totaldist/stepdist ="<<abs(totaldist/stepdist) << endl;
        return ;
    }

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.2;
    }

    yn=normal_depth(So, coefmanning, Q, y, Cm, B, SS);
    yc=critical_depth(Q, y, g, B, SS);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,B,SS,y);

    int numsteps=totaldist/fabs(stepdist)+1;

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(numsteps);

    QStringList headtext={"x","y Trap ","z+y"};

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->tableWidget->setHorizontalHeaderLabels(headtext);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(x)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("%1").arg(y)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("%1").arg(z+y)));

    resultatsfr0="i\tx[i]\ty2[i]\ty2+z[i]\n";

    resultatsfr0=resultatsfr0+"0\t"+QString::number(x)+
            "\t"+QString::number(y)+
            "\t"+QString::number(z+y)+"\n";

    //    double xx[numsteps];
    //    double zz[numsteps];

    y2[0]=y;
    xx[0]=x;
    zz[0]=z;
    for(int i = 1; i < numsteps; i++)
    {
        xx[i]=xx[i-1]+stepdist;
        zz[i]=zz[i-1]-stepdist*So;
    }
    y2[0]=y;

    int i,j;
    double ynew = y;
    double ylast = y;

    double maxit = 1000;
    double tol=ui->doubleSpinBox_epsilon->value();
    pd.setRange(0,numsteps-1);
    for (i=1; i<numsteps; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){break; }

        j=0;
        ynew=y2[i-1]+1/2.*stepdist*(fonctiondydx_for_RK4(y2[i-1],B,SS,Q,coefmanning,Cm,So,g)+
                fonctiondydx_for_RK4(y2[i-1],B,SS,Q,coefmanning,Cm,So,g)); ;
        while((fabs(ynew - ylast) > tol) & (j < maxit))
        {
            ylast = ynew ;
            ynew=y2[i-1]+1/2.*stepdist*(fonctiondydx_for_RK4(y2[i-1],B,SS,Q,coefmanning,Cm,So,g)+
                    fonctiondydx_for_RK4(ylast,B,SS,Q,coefmanning,Cm,So,g));
            j=j+1;
        }
        y2[i]=ynew;
        //cout<< "y2["<<i<<"]="<<y2[i] <<"j="<<j<< endl;
        if (isnan(y2[i]) || y2[i]<0 || (y2[i-1]<yc && y2[i]>yc)){ // la 3eme condition : pour eviter que la surface libre coupe yc (en S1, M3,...)
            //y2[i]=nan("");
            pd.close();
            QMessageBox::critical(this, tr("Erreur"),
                                  tr("Impossible de continuer le calcul, possible l'écoulement devient rapidement varié (ceci une fois le profile de "
                                     "la surface libre -S1, M3, A3,...- coupe la hauteur critique).\n"
                                     "Solutions possibles : diminuer la longueur du canal ou rectifier y0!\n"
                                     "Peut-être aussi c'est un problème de convergence, essayer de diminuer dx!")+
                                  tr("\nInformation utile! : l'erreur c'est produite à : x=")+QString::number(xx[i])+
                                  " (y2="+QString::number(y2[i])+").");
            break;
        }
        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(xx[i])+
                "\t"+QString::number(y2[i])+
                "\t"+QString::number(zz[i]+y2[i])+"\n";

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(xx[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(y2[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(zz[i]+y2[i])));
    }

    // Détermination Max et Mini de y2
    double highy,lowy;
    highy=y2[0];
    lowy=y2[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(y2[i]>highy){
            highy=y2[i];
        }else{
            if(y2[i]<lowy && y2[i]!=0){
                lowy=y2[i];
            }
        }
    }
    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,0,0,0);

    QVector<double> xplot(numsteps);
    QVector<double> zcplot(numsteps);
    QVector<double> zyplot(numsteps);
    QVector<double> zycplot(numsteps);
    QVector<double> zynplot(numsteps);

    y2[0]=y;
    xplot[0]=x;

    if (stepdist < 0){
        if (So>=0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;
        }
        if (So<0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }

    }else{
        if (So>=0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }
        if (So<0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;

        }
    }

    for(int i = 1; i < numsteps; i++)
    {
        xplot[i]=xplot[i-1]+stepdist;
        zcplot[i]=zcplot[i-1]-stepdist*So;
        zyplot[i]=zcplot[i]+y2[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;
    }

    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[numsteps]>highzyplot){
        highzyplot=zycplot[numsteps];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[numsteps]>highzyplot){
        highzyplot=zynplot[numsteps];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel(tr("Elévation (")+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if(ui->doubleSpinBox_S0->value()<=0 ){
        ui->customPlot->graph(3)->removeFromLegend();
    }else{
        ui->customPlot->graph(3)->setName(tr("y normale"));
    }
    ui->customPlot->replot();
}
void hydraulics_channel_gvf::methode_KM(){

    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double Cm;
    double g;
    double y=ui->doubleSpinBox_y0->value();
    double B=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();
    double z=0;
    double x=0;
    double stepdist=ui->doubleSpinBox_dx->value();
    double totaldist=ui->doubleSpinBox_L->value();

    if (totaldist<stepdist) {
        ui->doubleSpinBox_dx->setValue(totaldist/10);
    }

    if (abs(totaldist/stepdist) > 1000000 ){
        pd.close();
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de continuer, vous avez dépasser le nombre max de points de calcul (1000000), diminuer la longueur du canal ou augmenter dx!"));
        //cout<< "totaldist/stepdist ="<<abs(totaldist/stepdist) << endl;
        return ;
    }

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.2;
    }

    yn=normal_depth(So, coefmanning, Q, y, Cm, B, SS);
    yc=critical_depth(Q, y, g, B, SS);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,B,SS,y);

    int numsteps=totaldist/fabs(stepdist)+1;

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(numsteps);

    QStringList headtext={"x","y KM ","z+y"};

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->tableWidget->setHorizontalHeaderLabels(headtext);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(x)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("%1").arg(y)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("%1").arg(z+y)));

    resultatsfr0="i\tx[i]\ty2[i]\ty2+z[i]\n";

    resultatsfr0=resultatsfr0+"0\t"+QString::number(x)+
            "\t"+QString::number(y)+
            "\t"+QString::number(z+y)+"\n";

    // double xx[numsteps];
    // double zz[numsteps];

    y2[0]=y;
    xx[0]=x;
    zz[0]=z;
    for(int i = 1; i < numsteps; i++)
    {
        xx[i]=xx[i-1]+stepdist;
        zz[i]=zz[i-1]-stepdist*So;
    }
    y2[0]=y;
    double k1,k2,k3,k4,k5;
    //double error_truncation[numsteps];
    error_truncation[0]=0;

    pd.setRange(0,numsteps-1);
    int i;
    for (i=1; i<numsteps; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){break; }

        k1=1./3*stepdist*fonctiondydx_for_RK4(y2[i-1],B,SS,Q,coefmanning,Cm,So,g);
        k2=1./3*stepdist*fonctiondydx_for_RK4(y2[i-1]+k1,B,SS,Q,coefmanning,Cm,So,g);
        k3=1./3*stepdist*fonctiondydx_for_RK4(y2[i-1]+k2/2+k2/2,B,SS,Q,coefmanning,Cm,So,g);
        k4=1./3*stepdist*fonctiondydx_for_RK4(y2[i-1]+3./8*k1+9./3*k3,B,SS,Q,coefmanning,Cm,So,g);
        k5=1./3*stepdist*fonctiondydx_for_RK4(y2[i-1]+3./2*k1-9./2*k3+6*k4,B,SS,Q,coefmanning,Cm,So,g);
        error_truncation[i]=0.2*k1-0.9*k3+0.8*k4-0.1*k5;
        y2[i]=y2[i-1]+1/2.*(k1+4*k4+k5);
        if (isnan(y2[i]) || y2[i]<0 || (y2[i-1]<yc && y2[i]>yc)){ // la 3eme condition : pour eviter que la surface libre coupe yc (en S1, M3,...)
            y2[i]=nan("");
            pd.close();
            QMessageBox::critical(this, tr("Erreur"),
                                  tr("Impossible de continuer le calcul, possible l'écoulement devient rapidement varié (ceci une fois le profile de "
                                     "la surface libre -S1, M3, A3,...- coupe la hauteur critique).\n"
                                     "Solutions possibles : diminuer la longueur du canal ou rectifier y0!\n"
                                     "Peut-être aussi c'est un problème de convergence, essayer de diminuer dx!")+
                                  tr("\nInformation utile! : l'erreur c'est produite à : x=")+QString::number(xx[i])+" (y2="+QString::number(y2[i])+").");
            break;
        }
        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(xx[i])+
                "\t"+QString::number(y2[i])+
                "\t"+QString::number(zz[i]+y2[i])+"\n";
        //cout<< "y2["<<i<<"]="<<y2[i]<< endl;

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(xx[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(y2[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(zz[i]+y2[i])));
    }

    double somme_truncation=0;
    for(int i = 1; i < numsteps; i++)
    {
        somme_truncation=somme_truncation+error_truncation[i];
    }
    ///-----

    // Détermination Max et Mini de y2 et error_truncation
    double highy,lowy,lowerror_truncation,higherror_truncation;
    highy=y2[0];
    lowy=y2[0];
    lowerror_truncation=error_truncation[1];
    higherror_truncation=error_truncation[1];

    for(int i = 1; i < numsteps; i++)
    {
        if(y2[i]>highy){
            highy=y2[i];
        }else{
            if(y2[i]<lowy && y2[i]!=0){
                lowy=y2[i];
            }
        }
        //-----
        if(error_truncation[i]>higherror_truncation){
            higherror_truncation=error_truncation[i];
        }else{
            if(error_truncation[i]<lowerror_truncation){
                lowerror_truncation=error_truncation[i];
            }
        }
    }

    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,lowerror_truncation,higherror_truncation,somme_truncation);

    QVector<double> xplot(numsteps);
    QVector<double> zcplot(numsteps);
    QVector<double> zyplot(numsteps);
    QVector<double> zycplot(numsteps);
    QVector<double> zynplot(numsteps);

    y2[0]=y;
    xplot[0]=x;

    if (stepdist < 0){
        if (So>=0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;
        }
        if (So<0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }

    }else{
        if (So>=0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }
        if (So<0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;

        }
    }

    for(int i = 1; i < numsteps; i++)
    {
        xplot[i]=xplot[i-1]+stepdist;
        zcplot[i]=zcplot[i-1]-stepdist*So;
        zyplot[i]=zcplot[i]+y2[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;
    }
    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[numsteps]>highzyplot){
        highzyplot=zycplot[numsteps];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[numsteps]>highzyplot){
        highzyplot=zynplot[numsteps];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel(tr("Elévation (")+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if(ui->doubleSpinBox_S0->value()<=0 ){
        ui->customPlot->graph(3)->removeFromLegend();
    }else{
        ui->customPlot->graph(3)->setName(tr("y normale"));
    }
    ui->customPlot->replot();
}
void hydraulics_channel_gvf::methode_RK4(){

    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double Cm;
    double g;
    double y=ui->doubleSpinBox_y0->value();
    double B=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();
    double z=0;
    double x=0;
    double stepdist=ui->doubleSpinBox_dx->value();
    double totaldist=ui->doubleSpinBox_L->value();

    if (totaldist<stepdist) {
        ui->doubleSpinBox_dx->setValue(totaldist/10);
    }

    if (abs(totaldist/stepdist) > 1000000 ){
        pd.close();
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de continuer, vous avez dépasser le nombre max de points de calcul (1000000), diminuer la longueur du canal ou augmenter dx!"));
        //cout<< "totaldist/stepdist ="<<abs(totaldist/stepdist) << endl;
        return ;
    }

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.2;
    }

    yn=normal_depth(So, coefmanning, Q, y, Cm, B, SS);
    yc=critical_depth(Q, y, g, B, SS);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,B,SS,y);

    int numsteps=totaldist/fabs(stepdist)+1;

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(numsteps);

    QStringList headtext={"x","y RK4 ","z+y"};

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->tableWidget->setHorizontalHeaderLabels(headtext);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(x)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("%1").arg(y)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("%1").arg(z+y)));

    resultatsfr0="i\tx[i]\ty2[i]\ty2+z[i]\n";

    resultatsfr0=resultatsfr0+"0\t"+QString::number(x)+
            "\t"+QString::number(y)+
            "\t"+QString::number(z+y)+"\n";

    //    double xx[numsteps];
    //    double zz[numsteps];

    y2[0]=y;
    xx[0]=x;
    zz[0]=z;
    for(int i = 1; i < numsteps; i++)
    {
        xx[i]=xx[i-1]+stepdist;
        zz[i]=zz[i-1]-stepdist*So;
    }
    y2[0]=y;
    double k1,k2,k3,k4;
    pd.setRange(0,numsteps-1);
    for (int i=1; i<numsteps; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){break; }

        k1=stepdist*fonctiondydx_for_RK4(y2[i-1],B,SS,Q,coefmanning,Cm,So,g);
        k2=stepdist*fonctiondydx_for_RK4(y2[i-1]+k1/2,B,SS,Q,coefmanning,Cm,So,g);
        k3=stepdist*fonctiondydx_for_RK4(y2[i-1]+k2/2,B,SS,Q,coefmanning,Cm,So,g);
        k4=stepdist*fonctiondydx_for_RK4(y2[i-1]+k3,B,SS,Q,coefmanning,Cm,So,g);
        y2[i]=y2[i-1]+1/6.*(k1+2*k2+2*k3+k4);
        if (isnan(y2[i]) || y2[i]<0 || (y2[i-1]<yc && y2[i]>yc)){ // la 3eme condition : pour eviter que la surface libre coupe yc (en S1, M3,...)
            y2[i]=nan("");
            pd.close();
            QMessageBox::critical(this, tr("Erreur"),
                                  tr("Impossible de continuer le calcul, possible l'écoulement devient rapidement varié (ceci une fois le profile de "
                                     "la surface libre -S1, M3, A3,...- coupe la hauteur critique).\n"
                                     "Solutions possibles : diminuer la longueur du canal ou rectifier y0!\n"
                                     "Peut-être aussi c'est un problème de convergence, essayer de diminuer dx!")+
                                  tr("\nInformation utile! : l'erreur c'est produite à : x=")+QString::number(xx[i])+" (y2="+QString::number(y2[i])+").");
            break;
        }
        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(xx[i])+
                "\t"+QString::number(y2[i])+
                "\t"+QString::number(zz[i]+y2[i])+"\n";
        //cout<< "y2["<<i<<"]="<<y2[i]<< endl;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(xx[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(y2[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(zz[i]+y2[i])));
    }
    // Détermination Max et Mini de y2
    double highy,lowy;
    highy=y2[0];
    lowy=y2[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(y2[i]>highy){
            highy=y2[i];
        }else{
            if(y2[i]<lowy && y2[i]!=0){
                lowy=y2[i];
            }
        }
    }

    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,0,0,0);

    QVector<double> xplot(numsteps);
    QVector<double> zcplot(numsteps);
    QVector<double> zyplot(numsteps);
    QVector<double> zycplot(numsteps);
    QVector<double> zynplot(numsteps);

    y2[0]=y;
    xplot[0]=x;

    if (stepdist < 0){
        if (So>=0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;
        }
        if (So<0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }

    }else{
        if (So>=0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }
        if (So<0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;

        }
    }

    for(int i = 1; i < numsteps; i++)
    {
        xplot[i]=xplot[i-1]+stepdist;
        zcplot[i]=zcplot[i-1]-stepdist*So;
        zyplot[i]=zcplot[i]+y2[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;
    }
    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[numsteps]>highzyplot){
        highzyplot=zycplot[numsteps];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[numsteps]>highzyplot){
        highzyplot=zynplot[numsteps];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel(tr("Elévation (")+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if(ui->doubleSpinBox_S0->value()<=0 ){
        ui->customPlot->graph(3)->removeFromLegend();
    }else{
        ui->customPlot->graph(3)->setName(tr("y normale"));
    }
    ui->customPlot->replot();
}
void hydraulics_channel_gvf::methode_Bresse()
{
    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double b=ui->doubleSpinBox_b->value();

    double SS=0;//ui->doubleSpinBox_m->value(); //doit etre 0 pour Bresse!

    double Cm;
    double g;

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.2;
    }

    double R;
    double C;
    double A;
    double B;
    double eta1;
    double eta2;
    double phieta1;
    double phieta2;
    double dx;

    int npt=ui->spinBox_nbrePts->value()-1;

    //   double x[npt+1];
    //   double y[npt+1];

    x[0]=0;
    y[0]=ui->doubleSpinBox_y1->value();
    y[npt]=ui->doubleSpinBox_y2->value();

    double yn=normal_depth(So, coefmanning, Q, y[0], Cm, b, 0);
    double yc=critical_depth(Q, y[0], g, b, 0);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,b,SS,y[0]);

    if (ui->checkBox_useYi->isChecked()){
        for (int i=0; i<=npt; i++)
        {
            y[i]=ui->tableWidget->item(i,0)->text().toDouble();
        }
    }else{
        double dy=(y[npt]-y[0])/npt;
        for (int i=0; i<=npt; i++)
        {
            y[i+1]=y[i]+dy;
        }
    }

    // Détermination Max et Mini de y
    double highy,lowy;
    highy=y[0];
    lowy=y[0];

    for(int i = 1; i <= npt; i++)
    {
        if(y[i]>highy){
            highy=y[i];
        }else{
            if(y[i]<lowy && y[i]!=0){
                lowy=y[i];
            }
        }
    }

    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,0,0,0);

    if ((y[0]<=yc && y[npt]>=yc) || (y[npt]<=yc && y[0]>=yc)  || (y[0]<=yn && y[npt]>=yn) || (y[npt]<=yn && y[0]>=yn)){
        pd.close();
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de continuer, y1 et y2 sont de part et d'autre de yc ou yn!"));
        ui->tableWidget->clearContents();
        return;
    }

    pd.setRange(0,npt);

    double totaldist=0;
    int i;
    for (i=1; i<=npt; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){break; }

        R=1./2*(y[i-1]+y[i]);
        C=(1./coefmanning)*pow(R,1./6);
        A=yn/So;
        B=1-pow(C,2)*So/g;
        eta1=y[i-1]/yn;
        eta2=y[i]/yn;
        phieta1=1./6*log((pow(eta1,2)+eta1+1)/pow(eta1-1,2))-1./pow(3,1./3)*atan(pow(3,1./3)/(2*eta1+1));
        phieta2=1./6*log((pow(eta2,2)+eta2+1)/pow(eta2-1,2))-1./pow(3,1./3)*atan(pow(3,1./3)/(2*eta2+1));

        dx=A*((eta1-eta2)-B*(phieta1-phieta2));

        x[i]=x[i-1]-dx;

        //cout<<"y="<<y[i]<<"---"<<"x="<<x[i]<<"\n";
        totaldist=x[i];
    }

    resultatsfr0="i\ty[i]Bresse\tx[i]\n";


    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(npt+1);
    QStringList headtext={"y Bresse","x"};
    ui->tableWidget->setHorizontalHeaderLabels(headtext);
    for (i=0; i<=npt; i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(y[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(x[i])));

        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(y[i])+
                "\t"+QString::number(x[i])+"\n";
    }

    QVector<double> xplot(npt+1);
    QVector<double> zcplot(npt+1);
    QVector<double> zyplot(npt+1);
    QVector<double> zycplot(npt+1);
    QVector<double> zynplot(npt+1);

    xplot[0]=x[0];
    double z=0;

    if (So>=0){
        zcplot[0]=z+totaldist*abs(So);
        zyplot[0]=zcplot[0]+y[0];

        zycplot[0]=yc+totaldist*abs(So);
        zynplot[0]=yn+totaldist*abs(So);
    }
    if (So<0){
        zcplot[0]=z;
        zyplot[0]=zcplot[0]+y[0];

        zycplot[0]=yc;
        zynplot[0]=yn;

    }

    for(int i = 0; i <=npt; i++)
    {
        xplot[i]=x[i];
        if (totaldist < 0){
            zcplot[i]=abs(x[i])*So;
        }else{
            zcplot[i]=(abs(totaldist)-abs(x[i]))*So;
        }

    }

    for(int i = 0; i <=npt; i++)
    {
        zyplot[i]=zcplot[i]+y[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;

        //cout<<"zcplot="<<zcplot[i]<<"\n";
    }
    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i <= npt; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[npt]>highzyplot){
        highzyplot=zycplot[npt];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[npt]>highzyplot){
        highzyplot=zynplot[npt];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel("Elévation ("+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->replot();
}
void hydraulics_channel_gvf::methode_NR()
{
    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double Cm;
    double g;
    double y=ui->doubleSpinBox_y0->value();
    double B=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();
    double z=0;
    double x=0;
    double stepdist=ui->doubleSpinBox_dx->value();
    double totaldist=ui->doubleSpinBox_L->value();

    if (totaldist<stepdist) {
        ui->doubleSpinBox_dx->setValue(totaldist/10);
    }

    if (abs(totaldist/stepdist) > 1000000 ){
        pd.close();
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de continuer, vous avez dépasser le nombre max de points de calcul (1000000), diminuer la longueur du canal ou augmenter dx!"));
        //cout<< "totaldist/stepdist ="<<abs(totaldist/stepdist) << endl;
        return ;
    }

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.2;
    }

    yn=normal_depth(So, coefmanning, Q, y, Cm, B, SS);
    yc=critical_depth(Q, y, g, B, SS);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,B,SS,y);

    loop_step_haf(So,coefmanning,Q,Cm,g,y,B,SS,z,x,stepdist,totaldist);

    int numsteps=totaldist/fabs(stepdist)+1;

    // Détermination Max et Mini de y2
    double highy,lowy;
    highy=y2[0];
    lowy=y2[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(y2[i]>highy){
            highy=y2[i];
        }else{
            if(y2[i]<lowy && y2[i]!=0){
                lowy=y2[i];
            }
        }
    }
    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,0,0,0);

    QVector<double> xplot(numsteps);
    QVector<double> zcplot(numsteps);
    QVector<double> zyplot(numsteps);
    QVector<double> zycplot(numsteps);
    QVector<double> zynplot(numsteps);

    y2[0]=y;
    xplot[0]=x;

    if (stepdist < 0){
        if (So>=0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;
        }
        if (So<0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }

    }else{
        if (So>=0){
            zcplot[0]=z+totaldist*abs(So);
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc+totaldist*abs(So);
            zynplot[0]=yn+totaldist*abs(So);
        }
        if (So<0){
            zcplot[0]=z;
            zyplot[0]=zcplot[0]+y2[0];

            zycplot[0]=yc;
            zynplot[0]=yn;

        }
    }

    for(int i = 1; i < numsteps; i++)
    {
        xplot[i]=xplot[i-1]+stepdist;
        zcplot[i]=zcplot[i-1]-stepdist*So;
        zyplot[i]=zcplot[i]+y2[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;
    }
    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i < numsteps; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[numsteps]>highzyplot){
        highzyplot=zycplot[numsteps];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[numsteps]>highzyplot){
        highzyplot=zynplot[numsteps];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    //ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel(tr("Elévation (")+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if(ui->doubleSpinBox_S0->value()<=0 ){
        ui->customPlot->graph(3)->removeFromLegend();
    }else{
        ui->customPlot->graph(3)->setName(tr("y normale"));
    }
    ui->customPlot->replot();
}
void hydraulics_channel_gvf::methode_DirectStep(){
    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double b=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();

    double Cm;
    double g;

    if (ui->radioButton_SI->isChecked()){
        Cm=1;
        g=9.81;
    }else{
        Cm=1.486;
        g=32.174049;
    }

    int npt=ui->spinBox_nbrePts->value()-1;

    //    double x[npt+1];
    //    double y[npt+1];
    //    double dx[npt+1];
    dx[0]=0;
    x[0]=0;
    y[0]=ui->doubleSpinBox_y1->value();
    y[npt]=ui->doubleSpinBox_y2->value();

    double yn=normal_depth(So, coefmanning, Q, y[0], Cm, b, SS);
    double yc=critical_depth(Q, y[0], g, b, SS);
    QString profiletype=get_profile(So,coefmanning,Q,g,Cm,b,SS,y[0]);

    if (ui->checkBox_useYi->isChecked()){
        for (int i=0; i<=npt; i++)
        {
            y[i]=ui->tableWidget->item(i,0)->text().toDouble();
        }
    }else{
        double dy=(y[npt]-y[0])/npt;
        for (int i=0; i<=npt; i++)
        {
            y[i+1]=y[i]+dy;
        }
    }

    // Détermination Max et Mini de y
    double highy,lowy;
    highy=y[0];
    lowy=y[0];

    for(int i=1; i<=npt; i++)
    {
        if(y[i]>highy){
            highy=y[i];
        }else{
            if(y[i]<lowy && y[i]!=0){
                lowy=y[i];
            }
        }
    }
    // affichage des info
    afficher_information(yc,yn,profiletype,lowy,highy,0,0,0);

    if ((y[0]<=yc && y[npt]>=yc) || (y[npt]<=yc && y[0]>=yc)  || (y[0]<=yn && y[npt]>=yn) || (y[npt]<=yn && y[0]>=yn)){
        pd.close();
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Impossible de continuer, y1 et y2 sont de part et d'autre de yc ou yn!"));
        ui->tableWidget->clearContents();
        return;
    }

    double A1; // A
    double P1; // P
    double R1; // R
    double A2; // A
    double P2; // P
    double R2; // R
    double E1;
    double E2;
    double Sf1;
    double Sf2;
    double Sfbar;
    //cout<<"y="<<y[0]<<"---"<<"x="<<x[0]<<"\n";
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(npt+1);
    QStringList headtext={"y DirectStep","A","P","R","V","E","Sf","Sfmoy","dx","x"};
    resultatsfr0="i\ty[i] DirectStep\tA\tP\tR\tV\tE\tSf\tSfmoy\tdx\tx[i]\n";
    ui->tableWidget->setHorizontalHeaderLabels(headtext);

    A1 = y[0]*b + SS*y[0]*y[0]; // A
    P1 = b + 2*y[0]*sqrt(SS*SS + 1); // P
    R1 = A1/P1; // R
    E1= y[0]+pow(Q/A1,2)/(2*g);
    Sf1=pow((coefmanning*Q)/(Cm*A1*pow(R1,2./3)),2);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(y[0])));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("%1").arg(A1)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("%1").arg(P1)));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(tr("%1").arg(R1)));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(tr("%1").arg(Q/A1)));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(tr("%1").arg(E1)));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem(tr("%1").arg(Sf1)));
    ui->tableWidget->setItem(0,7,new QTableWidgetItem(tr("%1").arg("")));
    ui->tableWidget->setItem(0,8,new QTableWidgetItem(tr("%1").arg("")));
    ui->tableWidget->setItem(0,9,new QTableWidgetItem(tr("%1").arg("")));

    resultatsfr0=resultatsfr0+QString::number(0)+"\t"+QString::number(y[0])+"\t"+QString::number(A1)+
            "\t"+QString::number(P1)+"\t"+QString::number(R1)+"\t"+
            QString::number(Q/A1)+"\t"+QString::number(E1)+"\t"+QString::number(Sf1)+
            "\t"+""+"\t"+""+"\t"+""+"\n";

    double totaldist=0;
    pd.setRange(0,npt);
    for (int i=1; i<=npt; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){npt=i-1;break; } //12-6-2020

        A1 = y[i-1]*b + SS*y[i-1]*y[i-1]; // A
        P1 = b + 2*y[i-1]*sqrt(SS*SS + 1); // P
        R1 = A1/P1; // R
        A2 = y[i]*b + SS*y[i]*y[i]; // A
        P2 = b + 2*y[i]*sqrt(SS*SS + 1); // P
        R2 = A2/P2; // R
        E1= y[i-1]+pow(Q/A1,2)/(2*g);
        E2= y[i]+pow(Q/A2,2)/(2*g);
        Sf1=pow((coefmanning*Q)/(Cm*A1*pow(R1,2./3)),2);
        Sf2=pow((coefmanning*Q)/(Cm*A2*pow(R2,2./3)),2);
        Sfbar=(Sf1+Sf2)/2;
        dx[i]=(E2-E1)/(So-Sfbar);
        ///
        x[i]=x[i-1]+dx[i];

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(y[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(A2)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(P2)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(R2)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(tr("%1").arg(Q/A2)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(tr("%1").arg(E2)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(tr("%1").arg(Sf2)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(tr("%1").arg(Sfbar)));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(tr("%1").arg(dx[i])));
        ui->tableWidget->setItem(i,9,new QTableWidgetItem(tr("%1").arg(x[i])));

        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(y[i])+"\t"+QString::number(A2)+
                "\t"+QString::number(P2)+"\t"+QString::number(R2)+"\t"+
                QString::number(Q/A2)+"\t"+QString::number(E2)+"\t"+QString::number(Sf2)+
                "\t"+QString::number(Sfbar)+"\t"+QString::number(dx[i])+"\t"
                +QString::number(x[i])+"\n";

        //cout<<"y="<<y[i]<<"---"<<"x="<<x[i]<<"\n";
        totaldist=x[i];
    }

    QVector<double> xplot(npt+1);
    QVector<double> zcplot(npt+1);
    QVector<double> zyplot(npt+1);

    QVector<double> zycplot(npt+1);
    QVector<double> zynplot(npt+1);

    xplot[0]=x[0];
    double z=0;

    if (So>=0){
        zcplot[0]=z+totaldist*abs(So);
        zyplot[0]=zcplot[0]+y[0];

        zycplot[0]=yc+totaldist*abs(So);
        zynplot[0]=yn+totaldist*abs(So);
    }
    if (So<0){
        zcplot[0]=z;
        zyplot[0]=zcplot[0]+y[0];

        zycplot[0]=yc;
        zynplot[0]=yn;
    }

    for(int i = 0; i <=npt; i++)
    {
        xplot[i]=x[i];
        if (totaldist < 0){
            if (So<0) zcplot[i]=abs(x[i])*So+abs(totaldist*So);
            if (So>0) zcplot[i]=abs(x[i])*So; //+abs(totaldist*So); //HAF 30-08-2020
        }else{
            zcplot[i]=(abs(totaldist)-abs(x[i]))*So;
        }
        if (totaldist > 0 && So<0){
            zcplot[i]=abs(x[i]*So);
        }
    }

    for(int i = 0; i <=npt; i++)
    {
        zyplot[i]=zcplot[i]+y[i];

        zycplot[i]=zcplot[i]+yc;
        zynplot[i]=zcplot[i]+yn;
    }
    //--HAF---22-9-2020---------------
    double highzyplot;
    highzyplot=zyplot[0];

    for(int i = 1; i <= npt; i++)
    {
        if(zyplot[i]>highzyplot){
            highzyplot=zyplot[i];
        }
    }
    if (zycplot[0]>highzyplot){
        highzyplot=zycplot[0];
    }
    if (zycplot[npt]>highzyplot){
        highzyplot=zycplot[npt];
    }
    if (zynplot[0]>highzyplot){
        highzyplot=zynplot[0];
    }
    if (zynplot[npt]>highzyplot){
        highzyplot=zynplot[npt];
    }
    ymaxgraphe=highzyplot;
    //-------------------------------
    // plot
    ui->customPlot->clearGraphs();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 127))); // first graph will be filled with translucent blue
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::black)); // line color red for second graph
    ui->customPlot->graph(1)->setBrush(QBrush(Qt::gray)); // first graph will be filled with translucent blue

    ui->customPlot->addGraph();

    QPen hafDotPen;
    hafDotPen.setColor(Qt::red);
    hafDotPen.setStyle(Qt::DotLine);
    hafDotPen.setWidthF(1.15);
    ui->customPlot->graph(2)->setPen(hafDotPen);
    ui->customPlot->addGraph();
    hafDotPen.setColor(Qt::black);
    ui->customPlot->graph(3)->setPen(hafDotPen);

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xplot, zyplot);
    ui->customPlot->graph(0)->removeFromLegend();
    ui->customPlot->graph(1)->setData(xplot, zcplot);
    ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(2)->setData(xplot, zycplot);
    ui->customPlot->graph(2)->setName(tr("y critique"));
    ui->customPlot->graph(3)->setData(xplot, zynplot);
    ui->customPlot->graph(3)->setName(tr("y normale"));
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);

    ui->customPlot->legend->setVisible(true);

    ui->customPlot->yAxis->setLabel(tr("Elévation (")+ui->label_unite_y0->text()+")");
    ui->customPlot->xAxis->setLabel("x ("+ui->label_unite_y0->text()+")");

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->replot();

}
double hydraulics_channel_gvf::calcul_Energie_Specifique(double Q,double y,double A,double g){
    return y+pow(Q/A,2)/(2*g);

}
double hydraulics_channel_gvf::calcul_Sf(double Q,double n, double A, double R, double Cm){
    return pow(Q/conveyance(n,A,R,Cm),2);
}
///--------
void hydraulics_channel_gvf::remplire_Colonne_Yinpt(int npt){
    //HAF 25-8-2020
    if (ui->radioButton_Bresse->isChecked()){
        ui->tableWidget->setColumnCount(2);
        QStringList headtext={"y Bresse","x"};
        ui->tableWidget->setHorizontalHeaderLabels(headtext);
    }
    if (ui->radioButton_DirectStep->isChecked()){
        ui->tableWidget->setColumnCount(10);
        QStringList headtext={"y DirectStep","A","P","R","V","E","Sf","Sfmoy","dx","x"};
        ui->tableWidget->setHorizontalHeaderLabels(headtext);
    }
    //-----
    ui->tableWidget->clearContents();//15-6-2020 ubuntu
    ui->tableWidget->setRowCount(npt);
    y[0]=ui->doubleSpinBox_y1->value();
    y[npt]=ui->doubleSpinBox_y2->value();

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(y[0])));
    double dy=(y[npt]-y[0])/(npt-1);//15-6-2020 ubuntu
    for (int i=1; i<=npt; i++)//15-6-2020 ubuntu
    {
        y[i]=y[i-1]+dy;//15-6-2020 ubuntu
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(y[i])));
    }
}
void hydraulics_channel_gvf::remplire_Colonne_Yy1(double y1){
    //ui->checkBox_useYi->setChecked(false);
    int npt=ui->spinBox_nbrePts->value();
    ui->tableWidget->setRowCount(npt);
    //double y[npt]; //HAF 25-7-2020
    y[0]=y1;
    y[npt]=ui->doubleSpinBox_y2->value();

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(y[0])));
    double dy=(y[npt]-y[0])/(npt-1);
    for (int i=1; i<npt; i++)
    {
        y[i]=y[i-1]+dy;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(y[i])));
    }
}
void hydraulics_channel_gvf::remplire_Colonne_Yy2(double y2){
    //ui->checkBox_useYi->setChecked(false);
    int npt=ui->spinBox_nbrePts->value();
    ui->tableWidget->setRowCount(npt);
    //double y[npt]; //HAF 25-7-2020
    y[0]=ui->doubleSpinBox_y1->value();
    y[npt]=y2;

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(y[0])));
    double dy=(y[npt]-y[0])/(npt-1);
    for (int i=1; i<npt; i++)
    {
        y[i]=y[i-1]+dy;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(y[i])));
    }
}


void hydraulics_channel_gvf::desatif_noneed_Bresse_HAF(bool ischecked){
    if(ischecked==true && ui->comboBox_methode_calcul->currentIndex()==1){
        ui->doubleSpinBox_m->hide();
        ui->label_m->hide();
        ui->doubleSpinBox_L->hide();
        ui->label_L->hide();
        ui->label_unite_L->hide();
    }else{
        ui->doubleSpinBox_m->show();
        ui->label_m->show();
        ui->doubleSpinBox_L->show();
        ui->label_L->show();
        ui->label_unite_L->show();
    }
}
void hydraulics_channel_gvf::desatif_noneed_DirectStep(bool ischecked){
    if(ischecked==true && ui->comboBox_methode_calcul->currentIndex()==1){
        ui->doubleSpinBox_L->hide();
        ui->label_L->hide();
        ui->label_unite_L->hide();
    }else{
        ui->doubleSpinBox_L->show();
        ui->label_L->show();
        ui->label_unite_L->show();
    }
}
void hydraulics_channel_gvf::desatif_L_HAF(int currentIndex){
    if(currentIndex==1 && ui->radioButton_DirectStep->isChecked()){
        desatif_noneed_DirectStep(true);
    }else{
        desatif_noneed_Bresse_HAF(true);
    }
    if(currentIndex==1){
        ui->checkBox_useYi->show();
    }else{
        ui->checkBox_useYi->hide();
    }
    ui->stackedWidget_plot_imageEqts->setCurrentIndex(1);
    ui->tabWidget_parametres->setCurrentIndex(1);
}
void hydraulics_channel_gvf::afficher_information(double yc,double yn,
                                                  QString profiletype,double lowy,double highy
                                                  ,double lowerror_truncation,double higherror_truncation,double somme_truncation){

    yctext="yc="+QString::number(yc,'f',3);
    yntext="yn="+QString::number(yn,'f',3);
    ui->label_yc->setText(yctext);
    ui->label_yn->setText(yntext);

    if (profiletype=="M1"||profiletype=="M2"||profiletype=="M3") {
        ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/mildslope.png);");
        ui->label_exempleCourbeRemous->setStyleSheet("image: url(:/icons/M1M2M3.png);");
    }
    if (profiletype=="C1"||profiletype=="C3") {
        ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/criticalslope.png);");
        ui->label_exempleCourbeRemous->setStyleSheet("image: url(:/icons/C1C3.png);");
    }
    if (profiletype=="S1"||profiletype=="S2"||profiletype=="S3") {
        ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/steepslope.png);");
        ui->label_exempleCourbeRemous->setStyleSheet("image: url(:/icons/S1S2S3.png);");
    }
    if (profiletype=="H2"||profiletype=="H3") {
        ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/horizontalslope.png);");
        ui->label_exempleCourbeRemous->setStyleSheet("image: url(:/icons/H1H2H3.png);");
    }
    if (profiletype=="A2"||profiletype=="A3") {
        ui->label_typeCourbeRemous->setStyleSheet("image: url(:/icons/adverseslope.png);");
        ui->label_exempleCourbeRemous->setStyleSheet("image: url(:/icons/A1A2A3.png);");
    }

    QString resultatsinfo="";

    if (profiletype=="H2"||profiletype=="H3"){
        resultatsinfo=resultatsinfo+tr("Yn=Infinie (Canal horizontal)");
    }

    ui->label_yLow->setText("yLow="+QString::number(lowy));
    ui->label_yHigh->setText("yHigh="+QString::number(highy));


    if(ui->comboBox_methode_calcul->currentIndex()==0 && ui->comboBox_Methods->currentIndex()==2){
        resultatsinfo=resultatsinfo+ "\nlowerror_truncation="+
                QString::number(lowerror_truncation)
                +"\nhigherror_truncation="+QString::number(higherror_truncation)
                +"\nsomme_truncation="+QString::number(somme_truncation);
    }

    ui->label_info->setText(resultatsinfo);
    ui->label_Type_CR->setText(tr("Courbe de remous (type ")+profiletype+")");
}
///---------
double hydraulics_channel_gvf::fonctiondydx_for_RK4(double y,double B,double SS,double Q,double n,double Cm,double So,double g){
    unique_ptr<double[]> gp (new double[10]);
    gp = channel_geom(y, B, SS);
    double Sf = pow(Q/conveyance(n, gp[0], gp[2], Cm), 2.0);
    double f=(So-Sf)/(1-(pow(Q,2)*gp[9])/(g*pow(gp[0],3)));
    //gp.get_deleter();
    // gp.reset(nullptr);
    gp.release();
    return f;
}

///---------
double hydraulics_channel_gvf::standard_step_haf(double So, double n, double Q, double Cm, double g,
                                                 double y, double B, double SS, double z, double x, double stepdist)
{
    // define control section
    unique_ptr<double[]> gp (new double[10]);
    gp = channel_geom(y, B, SS);
    double E = y + z + 0.5*pow(Q/gp[0], 2.0)/g;
    double Sf = pow(Q/conveyance(n, gp[0], gp[2], Cm), 2.0);
    // define target section
    double znew = z - So*stepdist;
    double xnew = x + stepdist;
    // initial guess for y
    double ynew = y;
    double ylast = 999;
    int i = 0;
    double maxit = 1000;
    double tol=ui->doubleSpinBox_epsilon->value();
    //    double tol = 0.00001;
    double Sfbar;
    while((fabs(ynew - ylast) > tol) & (i < maxit))
    {
        ylast = ynew ;
        // calculate geometry using yguess
        unique_ptr<double[]> geomguess (new double[10]);
        geomguess = channel_geom(ylast, B, SS);
        // calculate Sfguess using geomguess
        double Sfguess = pow(Q/conveyance(n, geomguess[0], geomguess[2], Cm), 2.0);
        // calculate average Sf
        if (ui->checkBox_Sfmoy1->isChecked()){
            Sfbar = 0.5*(Sfguess + Sf);
        }else{
            Sfbar =pow(Q/((conveyance(n, geomguess[0], geomguess[2], Cm)+
                       conveyance(n, gp[0], gp[2], Cm))/2.0), 2.0);
        }
        // update ynew
        double j = 0;
        double dy = 9999;
        while((fabs(dy) > tol) & (j < maxit))
        {
            unique_ptr<double[]> geomopt (new double[10]);
            geomopt = channel_geom(ynew, B, SS);
            dy = (ynew + 0.5*pow(Q/geomopt[0], 2.0)/g + znew - E +
                    Sfbar*(xnew - x)) / (1 - geomopt[3]*Q*Q /
                    (g*pow(geomopt[0], 3.0)) -
                    (xnew - x)*(Sfguess*geomopt[3]/geomopt[0] +
                    (2.0/3.0)*Sfguess*geomopt[6]/geomopt[2]));
            ynew -= dy;
            j++;
            //  geomopt.get_deleter();
            // geomopt.reset(nullptr);
            geomopt.release();
        }
        i++;
        //geomguess.get_deleter();
        // geomguess.reset(nullptr);
        geomguess.release();
        //        cout<< "geomguess.get="<<geomguess.get()<< endl;
        //        if (geomguess.get() == nullptr){
        //           std::cout << "Foo is no longer owned by unique_ptr...\n";
        //        }
    }

    return ynew;
}
double* hydraulics_channel_gvf::loop_step_haf(double So, double n, double Q, double Cm,
                                              double g, double y, double B, double SS, double z, double x,
                                              double stepdist, double totaldist)
{
    int numsteps = totaldist/fabs(stepdist) + 1;

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(numsteps);

    QStringList headtext={"x","y NR","z+y"};

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->tableWidget->setHorizontalHeaderLabels(headtext);

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(tr("%1").arg(x)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(tr("%1").arg(y)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tr("%1").arg(z+y)));

    resultatsfr0="i\tx[i]\ty2[i]\ty2+z[i]\n";

    resultatsfr0=resultatsfr0+"0\t"+QString::number(x)+
            "\t"+QString::number(y)+
            "\t"+QString::number(z+y)+"\n";

    //    double xx[numsteps];
    //    double zz[numsteps];

    y2[0]=y;
    xx[0]=x;
    zz[0]=z;
    pd.setRange(0,numsteps-1);
    for(int i = 1; i < numsteps; i++)
    {
        pd.setValue(i);
        if(pd.wasCanceled()){break; }

        xx[i]=xx[i-1]+stepdist;
        zz[i]=zz[i-1]-stepdist*So;
        y2[i]= standard_step_haf(So, n, Q, Cm, g,y2[i-1], B, SS, zz[i-1],xx[i-1], stepdist);
        if (isnan(y2[i]) || y2[i]<0 || (y2[i-1]<yc && y2[i]>yc)){ // la 3eme condition : pour eviter que la surface libre coupe yc (en S1, M3,...)
            y2[i]=nan("");
            pd.close();
            QMessageBox::critical(this, tr("Erreur"),
                                  tr("Impossible de continuer le calcul, possible l'écoulement devient rapidement varié (ceci une fois le profile de "
                                     "la surface libre -S1, M3, A3,...- coupe la hauteur critique).\n"
                                     "Solutions possibles : diminuer la longueur du canal ou rectifier y0!\n"
                                     "Peut-être aussi c'est un problème de convergence, essayer de diminuer dx!")+
                                  tr("\nInformation utile! : l'erreur c'est produite à : x=")+QString::number(xx[i])+" (y2="+QString::number(y2[i])+").");
            break;
        }
        resultatsfr0=resultatsfr0+QString::number(i)+"\t"+QString::number(xx[i])+
                "\t"+QString::number(y2[i])+
                "\t"+QString::number(zz[i]+y2[i])+"\n";
        //cout<< "y2["<<i<<"]="<<y2[i]<< endl;

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(xx[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(y2[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(zz[i]+y2[i])));

    }
    return y2;
}
double hydraulics_channel_gvf::critical_depth(double Q, double yopt, double g, double B, double SS){
    // initialize
    double tol = 0.00001;
    int maxit = 1000;
    double dy = 9999;
    int i = 0;
    while((fabs(dy) > tol) & (i < maxit)){
        unique_ptr<double[]> gp (new double[10]);
        gp = channel_geom(yopt, B, SS);
        dy = (pow(gp[0], 3.0)/gp[3] - pow(Q, 2.0)/g) /
                (3.0*pow(gp[0], 2.0) - pow(gp[0], 3.0)*gp[5] /
                pow(gp[3], 2.0));
        yopt -= dy;
        i++;
        //gp.get_deleter();
        //gp.reset(nullptr);
        gp.release();
    }
    return(yopt);
}
double hydraulics_channel_gvf::normal_depth(double So, double n, double Q, double yopt, double Cm,
                                            double B, double SS){
    // initialize
    double tol = 0.00001;
    int maxit = 1000;
    double dy = 9999;
    int i = 0;
    while((fabs(dy) > tol) & (i < maxit)){
        unique_ptr<double[]> gp (new double[10]);
        gp = channel_geom(yopt, B, SS) ;
        dy = ( pow(gp[0], 5.0/3.0)/pow(gp[1], 2.0/3.0) - n*Q/(Cm*sqrt(So)) ) /
                ( gp[3]*(5.0/3.0)*pow(gp[0]/gp[1], 2.0/3.0) -
                (2.0/3.0)*gp[4]*pow(gp[0]/gp[1], 5.0/3.0) );
        yopt -= dy;
        i++;
        // gp.get_deleter();
        //gp.reset(nullptr);
        gp.release();
    }
    return(yopt);
}
///------------------
// create an owned vector initialized to zero
std::unique_ptr<double[]> new_vector(std::size_t n)
{
    return std::make_unique<double[]>(n);
}
std::unique_ptr<double[]> hydraulics_channel_gvf::channel_geom(double y, double B, double SS)
{
    std::unique_ptr<double[]> channel_geom = new_vector(10);
    //static double  channel_geom[10];
    // if SS is 0, channel is rectangular
    double A = y*B + SS*y*y; // A
    double P = B + 2*y*sqrt(SS*SS + 1); // P
    double R = A/P; // R
    double dAdy = B + 2*y*SS; // dAdy
    double dPdy = 2*sqrt(SS*SS + 1); // dPdy
    double dTdy = 2*SS; // dTdy
    double dRdy = dAdy/P - A*dPdy/(P*P); // dRdy
    double DH = A/dAdy;
    double ybar = y*(2*B + dAdy)/(3*(B + dAdy));

    double T=B+2*SS*y;  //la largeur de la surface libre 10-5-2020

    channel_geom[0]= A;
    channel_geom[1]= P;
    channel_geom[2]= R;
    channel_geom[3]= dAdy;
    channel_geom[4]= dPdy;
    channel_geom[5]= dTdy;
    channel_geom[6]= dRdy;
    channel_geom[7]= DH;
    channel_geom[8]= ybar;
    channel_geom[9]= T;
    return channel_geom;
    // channel_geom.get_deleter();
    //  channel_geom.reset(nullptr);
    // channel_geom.release();
}
double hydraulics_channel_gvf::conveyance(double n, double A, double R, double Cm) //débitance
{
    double C = Cm*A*pow(R, 2.0/3.0)/n;
    return(C);
}
double hydraulics_channel_gvf::froude(double Q, double g, double A, double DH)
{
    return((Q/A)/sqrt(DH*g));
}
void hydraulics_channel_gvf::Sfmoy_NR_HAF(){
    if (ui->comboBox_Methods->currentIndex()==0){
        ui->stackedWidget_Sfmoy->setCurrentIndex(0);
    }else{
        ui->stackedWidget_Sfmoy->setCurrentIndex(1);
    }
}
void hydraulics_channel_gvf::Affichage_ycyn_HAF(){
    double So=ui->doubleSpinBox_S0->value(); //Bed slope;
    double coefmanning=ui->doubleSpinBox_coefManning->value();
    double Q=ui->doubleSpinBox_Q->value();
    double b=ui->doubleSpinBox_b->value();
    double SS=ui->doubleSpinBox_m->value();
    double Cm;
    double g;
    double y0=ui->doubleSpinBox_y1->value();
    if (ui->radioButton_AngloSaxon->isChecked()){
        Cm=1.486;
        g=32.2;
    }else{
        Cm=1;
        g=9.81;
    }
    double yn=normal_depth(So, coefmanning, Q, y0, Cm, b, SS);
    double yc=critical_depth(Q, y0, g, b, SS);
    if(ui->doubleSpinBox_S0->value()<=0){
        ui->label_yn->hide();
        ui->label_unite_yn->hide();
    }else{
        ui->label_yn->show();
        ui->label_unite_yn->show();
    }
    yctext="yc="+QString::number(yc,'f',3);
    yntext="yn="+QString::number(yn,'f',3);
    ui->label_yc->setText(yctext);
    ui->label_yn->setText(yntext);

    ui->checkBox_useYi->setChecked(false);
    ui->tableWidget->clear();
}

void hydraulics_channel_gvf::SI_unite_HAF(){
    if (ui->radioButton_AngloSaxon->isChecked()){
        ui->label_unite_L->setText("ft");
        ui->label_unite_Q->setText("ft^3/s");
        ui->label_unite_dx->setText("ft");
        ui->label_unite_y0->setText("ft");
        ui->label_epsilon->setText("ft");
        ui->label_unite_B->setText("ft");
        ui->label_unite_yc->setText("ft");
        ui->label_unite_yn->setText("ft");
        ui->label_unite_y1->setText("ft");
        ui->label_unite_y2->setText("ft");
        ui->label_unite_yLow->setText("ft");
        ui->label_unite_yHigh->setText("ft");
    }else{
        ui->label_unite_L->setText("m");
        ui->label_unite_Q->setText("m^3/s");
        ui->label_unite_dx->setText("m");
        ui->label_unite_y0->setText("m");
        ui->label_epsilon->setText("m");
        ui->label_unite_B->setText("m");
        ui->label_unite_yc->setText("m");
        ui->label_unite_yn->setText("m");
        ui->label_unite_y1->setText("m");
        ui->label_unite_y2->setText("m");
        ui->label_unite_yLow->setText("m");
        ui->label_unite_yHigh->setText("m");
    }
}
QString hydraulics_channel_gvf::get_profile(double So, double n, double Q, double g, double Cm, double B, double SS, double y0){
    yc = critical_depth(Q, y0, g, B, SS);
    yn = normal_depth(So, n, Q, y0, Cm, B, SS);
    if(So < 0) // adverse slope
        if (y0 > yc)
            return("A2");
        else
            return("A3");
    else if (So == 0) // horizontal slope
        if(y0 > yc)
            return("H2");
        else
            return("H3");
    else if (yn > yc) // Mild slope
        if(y0 > yn)
            return("M1");
        else if (y0 > yc)
            return("M2");
        else
            return("M3");
    else if (yc > yn) // steep slope
        if (y0 > yc)
            return("S1");
        else if (yn > y0)
            return("S3");
        else
            return("S2");
    else // critical profile
        if (y0 > yc)
            return("C1");
        else
            return("C3");
}
void hydraulics_channel_gvf::copy_table_in_Clipboard(){
    pressePapiers->setText(resultatsfr0);
}

void hydraulics_channel_gvf::on_tabWidget_currentChanged(int index)
{
    if (index==1) calcul_HAF();
}


void hydraulics_channel_gvf::on_pushButton_about_clicked()
{
#if defined(Q_OS_ANDROID)
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("À propos"));
    msgBox.setTextFormat(Qt::RichText);
    QString pubabout=tr("Avec différentes méthodes numériques cette application simule l’écoulement graduellement varié (GVF) : Calcul des courbes de remous ; \n")+
            "Ver. "+ APP_VERSION +tr(" sur Linux, Windows et Android ; \n")+
            "("+ QString("%1").arg(BLD_DATE) +tr(") ; ")+
            "\n HAFIANE Mohamed ; e-mail for feedback: thakir.dz@gmail.com"+
            tr(" ou ")+
            "mohammed.hafiane@univ-saida.dz;\n\n"+
            tr("Page web : ")+
            "https://sites.google.com/site/courshaf; \n\n"+
            tr("Programmé avec C++ (mingw64) avec comme IDE (Qt Creator) et avec ")+
            " Qt Ver. " +QT_VERSION_STR;
    msgBox.setText(pubabout);
    msgBox.exec();
#else
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("À propos"));
    msgBox.setTextFormat(Qt::RichText);
    QString pubabout=tr("Avec différentes méthodes numériques cette application simule l’écoulement graduellement varié (GVF) : Calcul des courbes de remous ; \n")+
            "Ver. "+ APP_VERSION +tr(" sur Linux, Windows et Android ; \n")+
            "("+ QString("%1").arg(BLD_DATE) +tr(") ; ")+
            "\n HAFIANE Mohamed ; e-mail"+ tr(" pour (feedback) :")+" <a href=\"mailto:thakir.dz@gmail.com?"+
            "subject=About%20Application%20hydraulics_channel_gvf\">thakir.dz@gmail.com</a>"+
            tr(" ou ")+
            "<a href=\"mailto:mohammed.hafiane@univ-saida.dz?subject=About%20Application%20hydraulics_channel_gvf\">mohammed.hafiane@univ-saida.dz</a>"+" ;\n\n"+
            tr("Page web : ")+
            "<a href='https://sites.google.com/site/courshaf'>https://sites.google.com/site/courshaf</a>"+" ;\n\n"+
            tr("Programmé avec C++ (mingw64) avec comme IDE (Qt Creator) et avec ")+
            " Qt Ver. " +QT_VERSION_STR;

    msgBox.setText(pubabout);
    msgBox.exec();
#endif
}


void hydraulics_channel_gvf::on_pushButton_help_clicked()
{
    QString link = "https://sites.google.com/site/courshaf";
    QDesktopServices::openUrl(QUrl(link));
}


void hydraulics_channel_gvf::on_commandLinkButton_clicked()
{
    QMessageBox msgBoxinfodx(this);
    msgBoxinfodx.setWindowTitle(tr("Info"));
    /////msgBoxinfodx.setTextFormat(Qt::RichText);
    QString pubabout=tr("dx>0 si le point de contrôle y0 est à l'amont (le calcul sera de l'amont vers l'aval), cas d'écoulement torrentiel.")+
            "\n"+
            tr("dx<0 si le point de contrôle y0 est à l'aval (le calcul sera de l'aval vers l'amont),  cas d'écoulement fluvial.");
    msgBoxinfodx.setText(pubabout);
    msgBoxinfodx.exec();
}


void hydraulics_channel_gvf::on_commandLinkButton_2_clicked()
{
    QMessageBox msgBoxinfoNRcas2(this);
    msgBoxinfoNRcas2.setWindowTitle(tr("Info"));
    QString pubabout=tr("Pente moyenne du ligne de charge totale utilisée dans HEC-RAS par défaut, K est la débitance.");
    msgBoxinfoNRcas2.setText(pubabout);
    msgBoxinfoNRcas2.exec();
}


void hydraulics_channel_gvf::on_commandLinkButton_3_clicked()
{
    QMessageBox msgBoxinfoNR(this);
    msgBoxinfoNR.setWindowTitle(tr("Info"));
    QString pubabout=tr("Newton-Raphson : ")+tr("Se base sur le bilan de l'énergie spécifique : E=y+(V^2)/(2g)");
    msgBoxinfoNR.setText(pubabout);
    msgBoxinfoNR.exec();
}


void hydraulics_channel_gvf::on_commandLinkButton_4_clicked()
{
    QMessageBox msgBoxinfoBresse(this);
    msgBoxinfoBresse.setWindowTitle(tr("Info"));
    QString pubabout=tr("La méthode de Bresse est une méthode d'intégration directe valable uniquement pour un canal rectangulaire de section très large.");
    msgBoxinfoBresse.setText(pubabout);
    msgBoxinfoBresse.exec();
}


void hydraulics_channel_gvf::on_comboBox_Methods_currentIndexChanged(int index)
{
    if (index==0) Sfmoy_NR_HAF();
    if (index==1) Sfmoy_NR_HAF();
    if (index==2) Sfmoy_NR_HAF();
    if (index==3) Sfmoy_NR_HAF();
}

