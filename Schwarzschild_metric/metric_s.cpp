#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class SchwarszschildMetric {
  private:
    double M; //massa do buraco negro
    double rs; //raio de Schwarszschild

  public:
    SchwarszschildMetric(double mass) : M(mass) , rs(2 * mass) {}//construtor
    
  //métodos da classe
  
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

  //gerar os dados da métrica em um arquivo
  void generateMetricData(const string& filename){
    ofstream file(filename);

    file << "# r g_tt g_rr g_theta_theta g_phi_phi\n";//escreve no arquivo o cabeçalho

    for(double r = rs + 0.1; r <= rs + 10.0; r += 0.1){
      double g_tt = gtt(r);//variavel g_tt recebe o valor retornado pela função gtt
      double g_rr = grr(r);//variavel g_rr recebe o valor retornado pela função grr
      double g_theta_theta = gtheta_theta(r);//variavel g_theta_theta recebe o valor retornado pela função gtheta_theta
      double g_phi_phi = gphi_phi(r, M_PI / 4); //M_PI é o valor de pi incluso em cmath

      file << r << " " << g_tt << " " << g_rr << " " << g_theta_theta << " " << g_phi_phi << "\n";//escreve os valores para cada cooordenada da métrica no arquivo
    }

    file.close();//fecha o arquivo
  }   
};

int main() {

  SchwarszschildMetric metrica(1);//cria um objeto da classe SchwarszschildMetric com o nome metrica passando a massa fornecida
  metrica.generateMetricData("schwarszschild_metric.dat");//gera os dados da métrica pelo método generateMetricData

  cout << "Dados da métrica gerados em schwarszschild_metric.dat" << endl;


  SchwarszschildMetric metrica2(2);//objeto metrica2 para acessar a classe SchwarzschildMetric para M=2
  metrica2.generateMetricData("schwarszschild_metric2.dat");

  cout << "\nDados da métrica gerados em schwarszschild_metric2.dat" << endl;

  return 0;
}


