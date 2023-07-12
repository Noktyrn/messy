#include "battery_peukert.h"
#include "time.h"


void battery_peukert::set_attributes()
{
  out.set_timestep(1, sc_core::SC_SEC);
	
  out2.set_timestep(1, sc_core::SC_SEC);
	
  out3.set_timestep(1, sc_core::SC_SEC);


}

void battery_peukert::initialize()
{
 //out.initialize(4.2);
 k = 1.1;	
 Vnom=4.2;
}

// Process to calculate the Soc and the current LifeTime extimation
void battery_peukert::processing()
{
  double tmp_in;
  double tmp_lt;
  double t;
  sc_time time;
  tmp_in= in.read(); 

  time=sc_time_stamp();
  
  t=time.to_seconds(); 

  if(t==0){ 
    tmp_lt=0;
	
  }else{
    
    C=C*pow((Iprev/tmp_in), k-1);
	  if (Iprev==0)C=20800;
	    tmp_lt=C/(pow(tmp_in,k));
  } 
  soc=soc-((tmp_in)/20800);

  if(soc <= 0){
    cout<<"\nSoc is less then or equal to zero: "<<soc<<" @"<<sc_time_stamp()<<endl;
    sc_stop();
  }
  // Cprev=C;
  Iprev=in.read();

  out.write(4.2);

  out2.write(soc);

  out3.write(tmp_lt);
}