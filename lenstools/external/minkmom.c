#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Minkovski functional calculations
double mink_1_integrand(double gx,double gy){
	
	return 0.25*sqrt(pow(gx,2) + pow(gy,2));
	
}

double mink_2_integrand(double gx,double gy,double hxx,double hyy,double hxy){
	
	if(pow(gx,2)+pow(gy,2)==0.0){
		printf("WARNING: DIVIDE by 0: taking limit\n");
		printf("hxx=%e hyy=%e hxy=%e\n",hxx,hyy,hxy);
		return (2*hxy - hxx - hyy)/(4.0*M_PI);
	}
	else{
		return ((2*gx*gy*hxy-pow(gx,2)*hyy-pow(gy,2)*hxx)/(pow(gx,2)+pow(gy,2)))/(2.0*M_PI);
	}
}

void minkovski_functionals(double *map,long map_size,double sigma,double *gx,double *gy, double *hxx, double *hyy, double *hxy, int Nvalues, double *values,double *mink_0,double *mink_1,double *mink_2){
	
	int i,Nbins = Nvalues-1;
	long k;
	double integrand1,integrand2;
	
	for(k=0;k<map_size*map_size;k++){
		
		//calculate the minkovski functionals
		
		integrand1=mink_1_integrand(gx[k],gy[k]);
		integrand2=mink_2_integrand(gx[k],gy[k],hxx[k],hyy[k],hxy[k]);
		
		for(i=0;i<Nbins;i++){
			
			if(map[k]>=(values[i]+values[i+1])*sigma/2){
				
				mink_0[i] += 1.0/(map_size*map_size);
				
			}
			
			if(map[k]>=values[i]*sigma && map[k]<values[i+1]*sigma){
				
				mink_1[i] += integrand1/((map_size*map_size)*(values[i+1]-values[i]));
				mink_2[i] += integrand2/((map_size*map_size)*(values[i+1]-values[i]));
			
			}
		}
	
	}
}

void moments(double *map,long map_size, double *gx, double *gy, double *hxx, double *hyy, double *hxy, double *mean,double *variance, double *skeweness, double *kurtosis, double *fifth){
	
	long k;
	
	for(k=0;k<map_size*map_size;k++){
		
		//Do some map statistics here
		
		//Mean
		*mean += map[k]/(map_size*map_size);
		
		//Variance
		variance[0] += pow(map[k],2)/(map_size*map_size);
		variance[1] += (pow(gx[k],2) + pow(gy[k],2))/(map_size*map_size);
		
		//Skeweness
		skeweness[0] += pow(map[k],3)/(map_size*map_size);
		skeweness[1] += (pow(map[k],2)*(hxx[k]+hyy[k]))/(map_size*map_size);
		skeweness[2] += ((pow(gx[k],2) + pow(gy[k],2))*(hxx[k]+hyy[k]))/(map_size*map_size);
		
		//Kurtosis
		kurtosis[0] += pow(map[k],4)/(map_size*map_size);
		kurtosis[1] += (pow(map[k],3)*(hxx[k]+hyy[k]))/(map_size*map_size);
		kurtosis[2] += (map[k]*(pow(gx[k],2) + pow(gy[k],2))*(hxx[k]+hyy[k]))/(map_size*map_size);
		kurtosis[3] += pow((pow(gx[k],2) + pow(gy[k],2)),2)/(map_size*map_size);
		
		//Fifth moment
		*fifth += pow(map[k],5)/(map_size*map_size);
		
	}
	
}



