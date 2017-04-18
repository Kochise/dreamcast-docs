float f1(a,N) float*a;
{	float s0=0;
	float t0,t1;
	int i;
	t0=*a++;t1=*a++;
	do{	
		s0+=t0;t0=*a++;
		s0+=t1;t1=*a++;
		s0+=t0;t0=*a++;
		s0+=t1;t1=*a++;
	}while(--N);
	return s0;
}
float f2(a,N) float *a;
{	float s0=0,s1=0,s2=0,s3=0;
	float t0,t1;
	int i;
	t0=*a++;t1=*a++;
	do{
		s0+=t0;t0=*a++;  	
		s1+=t1;t1=*a++;
		s2+=t0;t0=*a++;
		s3+=t1;t1=*a++;
	}while(--N);
	return s0=s0+s1+s2+s3;
}

