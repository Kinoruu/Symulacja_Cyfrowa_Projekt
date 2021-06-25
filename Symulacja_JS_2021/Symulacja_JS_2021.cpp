#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <conio.h>
#include <fstream>
#include <ctime>
#include "Network.h"
#include "BaseStation.h"
#include "User.h"
#include "ResourceBlock.h"
#include "Simulator.h"
#include "Generators.h"
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

int main()
{
  int mode = 0;
  int view = 0;
  int initial_phase = 0;
  int simulation_time_ = 2000;
  int end = 0;
  int max_user_served_ = 0;
  int set_of_seeds;
  double lambda_;
  cout << "Choose end condition of simulation:  \n Press 1 Time \n Press 2 Number of user served after inital phase \n";
  cin >> end;
  if (end == 1)
  {
    cout << "Enter simulation time in ms: ";
    cin >> simulation_time_;
    //simulation_time_ *= 10;
  }
  else if (end == 2)
  {
    cout << "Enter number of users to be served: ";
    cin >> max_user_served_;
  }
  cout << "Enter time of initial phase in simulation in ms: ";
  cin >> initial_phase;
  cout << " Choose mode of simulation: \n Press 1 for step by step mode (next step by pressing Enter) \n Press 2 for continous mode \n \n";
  cin >> mode;
  cout << " Choose displayed information: \n Press 1 All information \n Press 2 Only User Arriving \n Press 3 Only Resource Block Allocation \n "
    "Press 4 Only Errors \n Press 5 Only User Propagation Change \n Press 6 Only Statistics \n Press 7 Only User removed information "
    "\n Press 8 Only information about number of users in system  \n \n";
  cin >> view;
  cout << "Choose set of seeds from 1 - 10 \n";
  cin >> set_of_seeds;
  cout << "Enter lambda:";
  cin >> lambda_;
  cout << "\n";


                                              // kod u¿yty do wygenerowania ziaren
  /*
  // Create random generator with arbitrary seed
  int initial_seed = 2109;
  auto generators = Generators(initial_seed);

  //Generation of Seeds
  int number_of_rands = 100000;
  int number_of_seeds = 50;
  vector<int> seeds;
  for (int i = 0; i < number_of_seeds; ++i){
    for (int j = 0; j < number_of_rands; ++j){
      generators.Rand();
    }
    seeds.push_back(generators.get_kernel());
  }
  ofstream output_file4("./ziarna.txt");
  ostream_iterator<int> output_iterator4(output_file4, "\n");
  copy(seeds.begin(), seeds.end(), output_iterator4);
  */

  vector<int> seeds;
  fstream inputfile;
  inputfile.open("ziarna.txt");
  string line;
  for(int i = 0 ; i < 50 ; i++)
  {
    getline(inputfile, line);
    seeds.push_back(stoi(line));
  } 
  inputfile.close();

  int seed_t, seed_d, seed_rk, seed_tau, seed_e;
  //for (int i = 0; i < 10; i++)
  for (int i = set_of_seeds-1; i < set_of_seeds; i++)
  {
    seed_t = seeds[i * 5];
    seed_d = seeds[(i * 5) + 1];
    seed_rk = seeds[(i * 5) + 2];
    seed_tau = seeds[(i * 5) + 3];
    seed_e = seeds[(i * 5) + 4];
    //cout << seed_t << " " << seed_d << " " << seed_rk << " " << seed_tau << " " << seed_e<< "\n";
    
    Network* network = new Network(seed_t, seed_d, seed_rk, seed_tau, seed_e, lambda_);
    Simulator simulator = Simulator(network);
    simulator.Simulation(simulation_time_, mode, view, initial_phase, end, max_user_served_, lambda_);

    double avg_awaiting_time_ = 0;    //u¿ywane podczas wyznaczania fazy pocz¹tkowej
    vector<int> uat = network->get_uat();
    for (size_t i = 0; i < uat.size(); ++i) { avg_awaiting_time_ += uat[i]; }
    avg_awaiting_time_ /= uat.size();
    //if ((view == 1) || (view == 6)) cout << "average awaiting time: " << avg_awaiting_time_ << "\n";
    //ofstream output_file9("./czas_oczekiwania_fp_" + to_string(i+1) + "_1.64.txt");
    //ostream_iterator<double> output_iterator9(output_file9, "\n");
    //copy(uat.begin(), uat.end(), output_iterator9);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double avg_system_bit_rate_ = 0;
    int asbt_iter = 0;
    vector<double> asbt = network->get_asbt();
    for (size_t i = 0; i < asbt.size(); ++i)
    {
      ++asbt_iter;
      if (asbt[i] == 0) { --asbt_iter; }
      else if (asbt[i] > 0) { avg_system_bit_rate_ += asbt[i]; }
    }
    avg_system_bit_rate_ /= asbt_iter;
    if ((view == 1) || (view == 6)) cout << "average system bit rate: " << avg_system_bit_rate_ << "\n";

    //ofstream output_file1("./srednia_przeplywnosc_systemu.txt");
    //ostream_iterator<double> output_iterator1(output_file1, "\n");
    //copy(asbt.begin(), asbt.end(), output_iterator1);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //double 
    avg_awaiting_time_ = 0;
    //vector<int> 
    uat = network->get_uat();
    for (size_t i = 0; i < uat.size(); ++i) { avg_awaiting_time_ += uat[i]; }
    avg_awaiting_time_ /= uat.size();
    if ((view == 1) || (view == 6)) cout << "average awaiting time: " << avg_awaiting_time_ << "\n";

    //ofstream output_file2("./czasy_oczekiwania_2_1.3.txt");
    //ostream_iterator<double> output_iterator2(output_file2, "\n");
    //copy(uat.begin(), uat.end(), output_iterator2);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double avg_user_bit_rate_ = 0;
    vector<double> aubr = network->get_aubr();
    for (size_t i = 0; i < aubr.size(); ++i) { avg_user_bit_rate_ += aubr[i]; }
    avg_user_bit_rate_ /= aubr.size();
    if ((view == 1) || (view == 6)) cout << "avg user bit rate: " << avg_user_bit_rate_ << "\n";

    //ofstream output_file3("./srednia_przep³ywnoœæ_po_u¿ytkownkach_" + to_string(i + 1) + "_fp200_l1.655.txt");
    //ostream_iterator<double> output_iterator3(output_file3, "\n");
    //copy(aubr.begin(), aubr.end(), output_iterator3);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<double> hw = network->get_hw();

    //ofstream output_file6("./hist_w .txt");
    //ostream_iterator<double> output_iterator6(output_file6, "\n");
    //copy(hw.begin(), hw.end(), output_iterator6);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<bool> hzj = network->get_hzj();

    //ofstream output_file7("./hist_zj .txt");
    //ostream_iterator<bool> output_iterator7(output_file7, "\n");
    //copy(hzj.begin(), hzj.end(), output_iterator7);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<int> hr = network->get_hr();

    //ofstream output_file8("./hist_r .txt");
    //ostream_iterator<int> output_iterator8(output_file8, "\n");
    //copy(hr.begin(), hr.end(), output_iterator8);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ((view == 1) || (view == 6)) cout << "number of users served by system: " << network->get_nous() << " (with initial phase " << network->get_nousu() << ")" << "\n";
    if ((view == 1) || (view == 6)) cout << "number of transmission failture system: " << network->get_noe() << " (with initial phase " << network->get_noeu() << ")" << "\n";
    if ((view == 1) || (view == 6)) cout << "number of all transmissions: " << network->get_nora() << " (with initial phase " << network->get_norau() << ")" << "\n";
    cout << "\n";
  }
}