#ifndef hydraulicschannelgvf_H
#define hydraulicschannelgvf_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot/qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.

#include <memory>  //7-6-2020
#include "math.h"
#include <utility>  //declarations of unique_ptr

namespace Ui {
class hydraulics_channel_gvf;
}

class hydraulics_channel_gvf : public QMainWindow
{
    Q_OBJECT

public:
    explicit hydraulics_channel_gvf(QWidget *parent = nullptr);
    ~hydraulics_channel_gvf();
    std::size_t array_size=1000000;
    double* y2 = new double[array_size];
    double* xx = new double[array_size];
    double* zz = new double[array_size];
    double* error_truncation = new double[array_size];

    double* x = new double[array_size];
    double* y = new double[array_size];
    double* dx = new double[array_size];

    //QVector<double>* xplot=new QVector<double>(1000000);
    //QVector<double>* zcplot=new QVector<double>(1000000);
    //QVector<double>* zyplot=new QVector<double>(1000000);
    //QVector<double>* zycplot=new QVector<double>(1000000);
    //QVector<double>* zynplot=new QVector<double>(1000000);

    double yn;
    double yc;

    QClipboard *pressePapiers = QApplication::clipboard();
    QString resultatsfr0;
    QProgressDialog pd;

public slots:

    void SI_unite_HAF();
    void copy_table_in_Clipboard();
    /////
    double* loop_step_haf(double So, double n, double Q, double Cm,
                          double g, double y, double B, double SS, double z, double x,
                          double stepdist, double totaldist);
    double standard_step_haf(double So, double n, double Q, double Cm, double g,
                             double y, double B, double SS, double z, double x, double stepdist);
    std::unique_ptr<double[]> channel_geom(double y, double B, double SS);
    //std::unique_ptr<double[]> new_vector(std::size_t n);
    double conveyance(double n, double A, double R, double Cm);
    double froude(double Q, double g, double A, double DH);

    double critical_depth(double Q, double yopt, double g, double B, double SS);
    double normal_depth(double So, double n, double Q, double yopt, double Cm, double B, double SS);
    QString get_profile(double So, double n, double Q, double g, double Cm, double B, double SS, double y0);

    double fonctiondydx_for_RK4(double y,double B,double SS,double Q,double n,double Cm,double So,double g);

    void methode_NR();
    void methode_Bresse();
    void methode_RK4();
    void methode_KM();
    void methode_Trap();
    void calcul_HAF();
    void desatif_noneed_Bresse_HAF(bool ischecked);
    void desatif_noneed_DirectStep(bool ischecked);
    void desatif_L_HAF(int currentIndex);

    void afficher_information(double yc,double yn,
                              QString profiletype,double lowy,double highy
                              ,double lowerror_truncation,
                              double higherror_truncation,double somme_truncation);
    void methode_DirectStep();
    double calcul_Energie_Specifique(double Q,double y,double A,double g);
    double calcul_Sf(double Q,double n, double A, double R, double Cm);

    void remplire_Colonne_Yinpt(int npt);
    void remplire_Colonne_Yy1(double y1);
    void remplire_Colonne_Yy2(double y2);

    void Sfmoy_NR_HAF();
    void saveGrapheToFile();
    void Affichage_ycyn_HAF();


private:
    Ui::hydraulics_channel_gvf *ui;
};

#endif // hydraulics_channel_gvf_H
