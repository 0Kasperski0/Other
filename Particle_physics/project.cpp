#include<iostream>
#include"TCanvas.h"
#include"TF1.h"
#include"TH1F.h"
#include"TH2F.h"
#include"TFile.h"
#include"TTree.h"
#include "TLegend.h"
#include "TStyle.h"
#include <TROOT.h>
#include <TChain.h>
#include <string>
#include "TSystem.h"
#include "TSystemDirectory.h"
#include <TLorentzVector.h>

using namespace std;


int main(void){
	gStyle->SetOptStat(0);
	gROOT->ProcessLine( "gErrorIgnoreLevel = 1001;");

	TFile* data = new TFile("data/D2hhh.root");		
	TTree* data_tree = (TTree*)data->Get("DecayTree");

	// ################################### INITALIZE VARIABLES ###################################

	
	Double_t h1_px, h1_py, h1_pz, h1_m;
	Double_t h2_px, h2_py, h2_pz, h2_m;
	Double_t h3_px, h3_py, h3_pz, h3_m;
	Double_t hh_px, hh_py, hh_pz, hh_m;
	Double_t h1_e, h2_e, h3_e;
	Double_t h1_piprop,h1_kprop,h2_piprop,h2_kprop,h3_piprop,h3_kprop;
	Double_t h1_ip, h2_ip, h3_ip;
	Double_t h1_ip_T, h2_ip_T, h3_ip_T;
	Double_t h1_origx,h1_origy,h1_origz;
	Double_t h2_origx,h2_origy,h2_origz;
	Double_t h3_origx,h3_origy,h3_origz;
	Double_t D_fd,D_m,D_p;


	double threshold_1=0;
	double threshold_2=0;
	double ip1_th,ip2_th,ip3_th;


	data_tree->SetBranchAddress("h1_IP", &h1_ip);
	data_tree->SetBranchAddress("h2_IP", &h2_ip);
	data_tree->SetBranchAddress("h3_IP", &h3_ip);

	data_tree->SetBranchAddress("h1_IP_TRUE", &h1_ip_T);
	data_tree->SetBranchAddress("h2_IP_TRUE", &h2_ip_T);
	data_tree->SetBranchAddress("h3_IP_TRUE", &h3_ip_T);


	data_tree->SetBranchAddress("h1_origX", &h1_origx);
	data_tree->SetBranchAddress("h1_origY", &h1_origy);
	data_tree->SetBranchAddress("h1_origZ", &h1_origz);
	
	data_tree->SetBranchAddress("h2_origX", &h2_origx);
	data_tree->SetBranchAddress("h2_origY", &h2_origy);
	data_tree->SetBranchAddress("h2_origZ", &h2_origz);

	data_tree->SetBranchAddress("h3_origX", &h3_origx);
	data_tree->SetBranchAddress("h3_origY", &h3_origy);
	data_tree->SetBranchAddress("h3_origZ", &h3_origz);
	
	data_tree->SetBranchAddress("D_FD", &D_fd);
	data_tree->SetBranchAddress("D_M", &D_m);
	data_tree->SetBranchAddress("D_P", &D_p);


	data_tree->SetBranchAddress("h1_ProbNNk", &h1_kprop);
	data_tree->SetBranchAddress("h1_ProbNNpi", &h1_piprop);

	data_tree->SetBranchAddress("h2_ProbNNk", &h2_kprop);
	data_tree->SetBranchAddress("h2_ProbNNpi", &h2_piprop);

	data_tree->SetBranchAddress("h3_ProbNNk", &h3_kprop);
	data_tree->SetBranchAddress("h3_ProbNNpi", &h3_piprop);


	data_tree->SetBranchAddress("h1_PX", &h1_px);
	data_tree->SetBranchAddress("h1_PY", &h1_py);
	data_tree->SetBranchAddress("h1_PZ", &h1_pz);
	data_tree->SetBranchAddress("h1_E", &h1_e);

	data_tree->SetBranchAddress("h2_PX", &h2_px);
	data_tree->SetBranchAddress("h2_PY", &h2_py);
	data_tree->SetBranchAddress("h2_PZ", &h2_pz);
	data_tree->SetBranchAddress("h2_E", &h2_e);
	
	data_tree->SetBranchAddress("h3_PX", &h3_px);
	data_tree->SetBranchAddress("h3_PY", &h3_py);
	data_tree->SetBranchAddress("h3_PZ", &h3_pz);
	data_tree->SetBranchAddress("h3_E", &h3_e);


	TLorentzVector p1,p2,p3,p4;
	int events=data_tree->GetEntries(); 


	// ################################### INITIALIZE HISOTGRAMS ###################################


	TH1F* h1_invariant_mass_distr = new TH1F("h1_invariant_mass_distr", "Invariant mass;Invariant mass [GeV];Events", 200, 0, 1.5);
	TH1F* h2_invariant_mass_distr = new TH1F("h2_invariant_mass_distr", "Invariant mass;Invariant mass [GeV];Events", 200, 0, 1.5);
	TH1F* h3_invariant_mass_distr = new TH1F("h3_invariant_mass_distr", "Invariant mass;Invariant mass [GeV];Events", 200, 0, 1.5);
	TH1F* sum_invariant_mass_distr = new TH1F("sum_invariant_mass_distr", "Invariant mass - prob.;Invariant mass [GeV];Events", 200, 1.6, 2.4);
	TH1F* sum_default_invariant_mass_distr = new TH1F("sum_default_invariant_mass_distr", "Invariant mass ;Invariant mass [GeV];Events", 200,  1.6, 2.4);
	TH1F* sum_ip_invariant_mass_distr = new TH1F("sum_ip_invariant_mass_distr", "Invariant mass - prob. + IP;Invariant mass [GeV];Events", 200, 1.6, 2.4);


	TH1F* h1_ip_dist = new TH1F("h1_ip_dist", "Impact parameter;Impact parameter;Events", 200, -700, 700);
	TH1F* h2_ip_dist = new TH1F("h2_ip_dist", "Impact parameter;Impact parameter;Events", 200, -700, 700);
	TH1F* h3_ip_dist = new TH1F("h3_ip_dist", "Impact parameter;Impact parameter;Events", 200, -700, 700);

	TH1F* part_1_dist = new TH1F("part_1_dist", "Impact parameter - both peaks;Impact parameter;Events", 200, -700, 700);
	TH1F* part_2_dist = new TH1F("part_2_dist", "Impact parameter - both peaks;Impact parameter;Events", 200, -700, 700);

	TH1F* h1_ip_dist_TR = new TH1F("h1_ip_dist_TR", "Impact parameter - TRUE;Impact parameter;Events", 200, -0.1, 3);
	TH1F* h2_ip_dist_TR = new TH1F("h2_ip_dist_TR", "Impact parameter - TRUE;Impact parameter;Events", 200, -0.1, 3);
	TH1F* h3_ip_dist_TR = new TH1F("h3_ip_dist_TR", "Impact parameter - TRUE;Impact parameter;Events", 200, -0.1, 3);

	TH1F* d_fd_dist = new TH1F("d_fd_dist", "D meson flight distance;Distance [mm];Events", 200, -2,40);		
	TH1F* d_life_dist = new TH1F("d_life_dist", "D meson life time;Life Time [s];Events", 200, 0,0.00000000005);		

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MAIN LOOP %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%	Parametry selekcji  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	threshold_1=0.8;
	threshold_2=0.2;
	ip1_th=ip2_th=1E+10;	// pozostałość po pierwotnych próbach - ustalony tak wysoki, żeby nie wpływał na selekcję
	ip3_th=1E+10;
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	for (int i = 0; i < events; ++i)
	{
		data_tree->GetEntry(i);

        p1.SetPxPyPzE(h1_px,
                      h1_py,
                      h1_pz,
                      h1_e); 
       

        p2.SetPxPyPzE(h2_px,
                      h2_py,
                      h2_pz,
                      h2_e); 


        p3.SetPxPyPzE(h3_px,
                      h3_py,
                      h3_pz,
                      h3_e); 

        h1_invariant_mass_distr->Fill(p1.M());
        h2_invariant_mass_distr->Fill(p2.M());
        h3_invariant_mass_distr->Fill(p3.M());

        h1_ip_dist->Fill(h1_ip);
        h2_ip_dist->Fill(h2_ip);
        h3_ip_dist->Fill(h3_ip);

        h1_ip_dist_TR->Fill(h1_ip_T);
        h2_ip_dist_TR->Fill(h2_ip_T);
        h3_ip_dist_TR->Fill(h3_ip_T);


        sum_default_invariant_mass_distr->Fill((p1+p2+p3).M());

        if ((h1_kprop>threshold_1 && h1_piprop<(threshold_2)) &&
        	(h2_piprop>threshold_1 && h2_kprop<(threshold_2)) &&
        	(h3_piprop>threshold_1 && h3_kprop<(threshold_2)))
        {
        
	        sum_invariant_mass_distr->Fill((p1+p2+p3).M());

	        if ((p1+p2+p3).M()<1.9)
	        {
                part_1_dist->Fill(h1_ip);
			    d_fd_dist->Fill(D_fd);
				d_life_dist->Fill(0.001*D_fd*D_p/(D_m*300000000)); //zakładam ,że D_fd w mm   	                
	        }

	        if ((p1+p2+p3).M()>1.9)
	        {
                part_2_dist->Fill(h1_ip);
	        }

        	if ((abs(h1_ip)<ip1_th) && (h1_ip)>=0 &&
        	   (abs(h2_ip)<ip2_th) && (h2_ip)>=0 &&
        	   (abs(h3_ip)<ip3_th) && (h3_ip)>=0 )
        	{
        		sum_ip_invariant_mass_distr->Fill((p1+p2+p3).M());
        	}        	

        	continue;

        }

        if ((h1_piprop>threshold_1 && h1_kprop<(threshold_2)) &&
        	(h2_kprop>threshold_1 && h2_piprop<(threshold_2)) &&
        	(h3_piprop>threshold_1 && h3_kprop<(threshold_2)))
        {
        	
        	sum_invariant_mass_distr->Fill((p1+p2+p3).M());
     	
	        if ((p1+p2+p3).M()<1.9)
	        {
                part_1_dist->Fill(h1_ip);
			    d_fd_dist->Fill(D_fd);
				d_life_dist->Fill(0.001*D_fd*D_p/(D_m*300000000));                
	        }

	        if ((p1+p2+p3).M()>1.9)
	        {
                part_2_dist->Fill(h1_ip);
        	}       	

        	if ((abs(h1_ip)<ip1_th) && (h1_ip)>=0 &&
        	   (abs(h2_ip)<ip2_th) && (h2_ip)>=0 &&
        	   (abs(h3_ip)<ip3_th) && (h3_ip)>=0 )
        	{
        		sum_ip_invariant_mass_distr->Fill((p1+p2+p3).M());
        	}

        	continue;

        }

        if ((h1_piprop>threshold_1 && h1_kprop<(threshold_2)) &&
        	(h2_piprop>threshold_1 && h2_kprop<(threshold_2)) &&
        	(h3_kprop>threshold_1 && h3_piprop<(threshold_2)))
        {
	        sum_invariant_mass_distr->Fill((p1+p2+p3).M());
 	
	        if ((p1+p2+p3).M()<1.9)
	        {
                part_1_dist->Fill(h1_ip);
		        d_fd_dist->Fill(D_fd);
				d_life_dist->Fill(0.001*D_fd*D_p/(D_m*300000000)); 	                
	        }

	        if ((p1+p2+p3).M()>1.9)
	        {
	            part_2_dist->Fill(h1_ip);
	        }       	

        	if ((abs(h1_ip)<ip1_th) && (h1_ip)>=0 &&
        	   (abs(h2_ip)<ip2_th) && (h2_ip)>=0 &&
        	   (abs(h3_ip)<ip3_th) && (h3_ip)>=0 )
        	{
	       		sum_ip_invariant_mass_distr->Fill((p1+p2+p3).M());    		
        	}        	
			continue;
        }                
	}




	// ################################### PLOTTING ###################################


	TCanvas* canvas = new TCanvas("canvas", "canvas", 1280, 720);

	std::string filename_2d = "plots/results.pdf";

	canvas->SaveAs((filename_2d + "[").c_str());

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	d_fd_dist->Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();


	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	TF1 *f_life_test = new TF1("f_life_test","[0]*exp([1]*x)", 0.0000000000002, 0.000000000022);
	d_life_dist->Draw();
	d_life_dist->Fit(f_life_test,"R");

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	h1_invariant_mass_distr->SetLineColor(1);
  	h2_invariant_mass_distr->SetLineColor(2);
  	h3_invariant_mass_distr->SetLineColor(4);

	h2_invariant_mass_distr->Draw();
	h1_invariant_mass_distr->Draw("same");
	h3_invariant_mass_distr->Draw("same");

		TLegend leg(0.6, 0.77, 0.7, 0.87  );
	leg.AddEntry(h1_invariant_mass_distr, "h1","l");
    leg.AddEntry(h2_invariant_mass_distr, "h2","l");
    leg.AddEntry(h3_invariant_mass_distr, "h3","l");
	leg.Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	TF1 *g1 = new TF1("g1","gaus",1.84,1.9);
	sum_default_invariant_mass_distr->SetLineColor(2);
	sum_ip_invariant_mass_distr->SetLineColor(3);

	sum_default_invariant_mass_distr->Draw();
	sum_invariant_mass_distr->Draw("same");
	sum_invariant_mass_distr->Fit(g1,"R");
	sum_ip_invariant_mass_distr->Draw("same");

		TLegend leg2(0.6, 0.77, 0.7, 0.87);
	leg2.AddEntry(sum_default_invariant_mass_distr, "before cuts","l");
    leg2.AddEntry(sum_invariant_mass_distr, "with cuts","l");
    leg2.AddEntry(sum_ip_invariant_mass_distr, "with cuts - ip","l");
	leg2.Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	sum_invariant_mass_distr->Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	sum_ip_invariant_mass_distr->Draw();
	sum_ip_invariant_mass_distr->Fit(g1,"R");

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();	

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	h1_ip_dist->SetLineColor(1);
  	h2_ip_dist->SetLineColor(2);
  	h3_ip_dist->SetLineColor(4);

	h1_ip_dist->Draw();
	h2_ip_dist->Draw("same");
	h3_ip_dist->Draw("same");

		TLegend leg3(0.6, 0.77, 0.7, 0.87  );
	leg3.AddEntry(h1_ip_dist, "h1","l");
    leg3.AddEntry(h2_ip_dist, "h2","l");
    leg3.AddEntry(h3_ip_dist, "h3","l");
	leg3.Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


	part_1_dist->SetLineColor(1);
  	part_2_dist->SetLineColor(2);

	part_1_dist->Draw();
	part_2_dist->Draw("same");


		TLegend leg5(0.6, 0.77, 0.7, 0.87  );
	leg5.AddEntry(part_1_dist, "P1","l");
    leg5.AddEntry(part_2_dist, "P2","l");
	leg5.Draw();

	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	h1_ip_dist_TR->SetLineColor(1);
  	h2_ip_dist_TR->SetLineColor(2);
  	h3_ip_dist_TR->SetLineColor(4);

	h1_ip_dist_TR->Draw();
	h2_ip_dist_TR->Draw("same");
	h3_ip_dist_TR->Draw("same");

		TLegend leg4(0.6, 0.77, 0.7, 0.87  );
	leg4.AddEntry(h1_ip_dist_TR, "h1","l");
    leg4.AddEntry(h2_ip_dist_TR, "h2","l");
    leg4.AddEntry(h3_ip_dist_TR, "h3","l");
	leg4.Draw();	
	canvas->SaveAs(filename_2d.c_str());
	canvas->Clear();

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
	canvas->SaveAs((filename_2d + "]").c_str());


	// ################################### REMOVING HISTOS ###################################


	delete h1_invariant_mass_distr,h2_invariant_mass_distr,h3_invariant_mass_distr,sum_invariant_mass_distr,sum_default_invariant_mass_distr,
	sum_ip_invariant_mass_distr,h1_ip_dist,h2_ip_dist,h3_ip_dist,part_1_dist,part_2_dist,h1_ip_dist_TR,h2_ip_dist_TR,h3_ip_dist_TR,d_fd_dist,
	d_life_dist;

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	cout<<"Fin."<<'\n';
	return 0;
}