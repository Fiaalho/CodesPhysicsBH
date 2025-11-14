#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

class SchwarszschildMetric {
  private:
    double M; //mass of the black hole
    double rs; //Schwarzschild radius

  public:
    SchwarszschildMetric(double mass) : M(mass) , rs(2 * mass) {}//constructor
    
  //class methods
  
  double gtt(double r) {
      return -(1.0 - rs / r);
    }

  double grr(double r) {
      return 1.0 / (1.0 - rs / r);
    }

    double gtheta_theta(double r) {
      return r * r;
    }

    double gphi_phi(double r, double theta) {
      return r * r * sin(theta) * sin(theta);
    }

  //generate metric data in a file
  void generateMetricData(const string& filename){
    ofstream file(filename);

    file << "# r g_tt g_rr g_theta_theta g_phi_phi\n";//write header to file
    for(double r = rs + 0.1; r <= rs + 10.0; r += 0.1){
      double g_tt = gtt(r);//variable g_tt receives the value returned by the function gtt
      double g_rr = grr(r);//variable g_rr receives the value returned by the function grr
      double g_theta_theta = gtheta_theta(r);//variable g_theta_theta receives the value returned by the function gtheta_theta
      double g_phi_phi = gphi_phi(r, M_PI / 4); //M_PI is the value of pi included in cmath

      file << r << " " << g_tt << " " << g_rr << " " << g_theta_theta << " " << g_phi_phi << "\n";//write the values for each metric coordinate to the file
    }

    file.close();//close the file
  }   
};

int main() {

  SchwarszschildMetric metric(1);//create an object of the class SchwarszschildMetric named metric passing the provided mass
  metric.generateMetricData("schwarszschild_metric.dat");//generate metric data using the generateMetricData method

  cout << "Metric data generated in schwarszschild_metric.dat" << endl;

  SchwarszschildMetric metric2(2);//object metric2 to access the SchwarzschildMetric class for M=2
  metric2.generateMetricData("schwarszschild_metric2.dat");

  cout << "\nMetric data generated in schwarszschild_metric2.dat" << endl;

  return 0;
}


