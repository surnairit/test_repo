//compile with " g++ -g -I${ROOTSYS}/include 3600_histo.cpp  `root-config --glibs`  "

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>
#include "TMath.h"
#include <TApplication.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TRandom.h"
#include "TDirectoryFile.h"
#include "TGraph.h"


using namespace std;
main()



{
 TApplication app("my_app",0,0);


  char histname[100];

  TFile *fileout = new TFile("3600_histograms.root","RECREATE");

  TH1F *pixel_histogram[3601];



  for (int j=0;j<3601;j++) {
	sprintf(histname,"pixels_fired=%i",j);
	pixel_histogram[j] = new TH1F(histname,histname,20000.,0.5,20000.5); 
  }


  srand(time(0));
  int InciNumPhotons=1, PhotonCount=0, NumPixelFired=0, TotEvents=5000, EventNum=0;
  double pixelsize, activesize, deadpix;
  pixelsize=50./60.0, activesize=39./50.0, deadpix=5.5/50.0;
  double xrandNum=0, yrandNum=0;
  int xpix=0, ypix=0;
  double xextra, yextra, average=0, sum=0;
  int PixelID[60][60]={{0}};
  ofstream outfile("PixelCountsv2Direct.txt");
  outfile<<"EventNumber"<<"\t"<<"InputPhotons"<<"\t"<<"ObservedPixels"<<endl;
//  while(InciNumPhotons<1500){
  while(InciNumPhotons<20001){
    for(int k=0;k<TotEvents;k++){
      EventNum++;
      while(PhotonCount<InciNumPhotons){
        xrandNum=60.0*rand()/RAND_MAX; 
        yrandNum=60.0*rand()/RAND_MAX;  
        xpix=xrandNum;  
        ypix=yrandNum; 
        xextra=xrandNum-xpix; 
        yextra=yrandNum-ypix; 
        if((xextra>deadpix)&&(xextra<(pixelsize-deadpix))&&(yextra>deadpix)&&(yextra<(pixelsize-deadpix))){
          PhotonCount+=1; 
          PixelID[xpix][ypix]++;
        } 
      }
      for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
          if(PixelID[i][j]>0){
            NumPixelFired+=1;			//count the fired pixels 
          }
        }
      } 
      //outfile<<EventNum<<"\t"<<InciNumPhotons<<"\t"<<NumPixelFired<<endl;	//store the number of fired pixels

	pixel_histogram[NumPixelFired]->Fill(InciNumPhotons);

      sum=sum+NumPixelFired;
      NumPixelFired=0;
      PhotonCount=0;
      xpix=0; ypix=0;
      xextra=0.0; yextra=0.0;
      for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
          PixelID[i][j]=0; 
        }
      } 
    }
    
  average=sum/TotEvents;
  outfile<<EventNum+1<<"\t"<<InciNumPhotons<<"\t"<<average<<endl; 
  //cout<<InciNumPhotons<<"\t\t"<<average<<endl;  
  cout <<InciNumPhotons<<endl;
  InciNumPhotons+=1;
  sum=0;
  average=0;
  EventNum=0;
  }
/* 
 InciNumPhotons=1501;
   while(InciNumPhotons<20001){
    for(int k=0;k<TotEvents;k++){
      EventNum++;
      while(PhotonCount<InciNumPhotons){
        xrandNum=60.0*rand()/RAND_MAX; 
        yrandNum=60.0*rand()/RAND_MAX;  
        xpix=xrandNum;  
        ypix=yrandNum; 
        xextra=xrandNum-xpix; 
        yextra=yrandNum-ypix; 
        if((xextra>deadpix)&&(xextra<(pixelsize-deadpix))&&(yextra>deadpix)&&(yextra<(pixelsize-deadpix))){
          PhotonCount+=1; 
          PixelID[xpix][ypix]++;
        } 
      }
      for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
          if(PixelID[i][j]>0){
            NumPixelFired+=1;			//count the fired pixels 
          }
        }
      } 
      //outfile<<EventNum<<"\t"<<InciNumPhotons<<"\t"<<NumPixelFired<<endl;	//store the number of fired pixels
      sum=sum+NumPixelFired;
      NumPixelFired=0;
      PhotonCount=0;
      xpix=0; ypix=0;
      xextra=0.0; yextra=0.0;
      for(int i=0;i<60;i++){
        for(int j=0;j<60;j++){
          PixelID[i][j]=0; 
        }
      } 
    }
    
  average=sum/TotEvents;
  outfile<<EventNum+1<<"\t"<<InciNumPhotons<<"\t"<<average<<endl; 
  cout<<InciNumPhotons<<"\t\t"<<average<<endl;  
  InciNumPhotons+=100;;
  sum=0;
  average=0;
  EventNum=0;
  }

*/
  outfile.close();

  fileout->cd();
  for (int j=0;j<3601;j++) {
	sprintf(histname,"pixels_fired=%i",j);
	pixel_histogram[j]->Write(histname);
  }

  cout<<"File Ready"<<endl;




}

