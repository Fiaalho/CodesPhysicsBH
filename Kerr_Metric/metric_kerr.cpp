#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

class KerrMetric {
  private:
    double M;
    double a;
    double r;//radius of the horizon
    
  public:
    KerrMetric(double mass, double spin): M(mass), a(spin), r(mass + sqrt(mass*mass - spin*spin)) {}//constructor


    //sigma value
    double sigma(double r, double theta) {
        return r*r + a*a * cos(theta)*cos(theta);
    }

    double delta(double r){
        return (r*r) - 2*M*r + a*a;
    }

    double g_tt(double r, double theta) {
        double sig = sigma(r, theta);
        return -(1 - (2*M*r)/sig);
    }

    double g_tphi(double r, double theta) {
        double sig = sigma(r, theta);
        return -(4*M*r*a*sin(theta)*sin(theta))/sig;
    }

    double g_rr(double r, double theta) {
        double sig = sigma(r, theta);
        double del = delta(r);
        return sig/del;
    }

    double g_thetatheta(double r, double theta) {
        double sig = sigma(r, theta);
        return sig;
    }

    double g_phiphi(double r, double theta) {
        double sig = sigma(r, theta);
        double del = delta(r);
        return (sin(theta)*sin(theta)) * (r*r + a*a)*(r*r + a*a)-a*a*del*sin(theta)*sin(theta)/sig;
    }

    // Generate metric data and write to file
    void generateMetricData(const string& filename){
      ofstream file(filename);

      file << "r gtt gtphi grr gthetatheta gphiphi\n";

      double theta = M_PI/6;

      for(double rn=r+0.01; rn<=r+10.0; rn+=0.1){
        double gtt = g_tt(rn, theta);
        double gtphi = g_tphi(rn, theta);
        double grr = g_rr(rn, theta);
        double gthetatheta = g_thetatheta(rn, theta);
        double gphiphi = g_phiphi(rn, theta);

        file << rn << " " << gtt << " " << gtphi << " " << grr << " " << gthetatheta << " " << gphiphi << "\n";
      }
      file.close();
    }
};

int main(){
  KerrMetric k(1.0, 0.6);
  k.generateMetricData("kerr_metric.dat");

  KerrMetric k2(2.0, 1.0);
  k2.generateMetricData("kerr_metric2.dat");
}