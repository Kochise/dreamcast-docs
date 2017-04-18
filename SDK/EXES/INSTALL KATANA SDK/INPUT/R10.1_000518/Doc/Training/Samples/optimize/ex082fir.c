float fir1_1(n,cp,xp) int n; float*cp,*xp;
{	float sum=0;
	do{	sum+=*cp++ * *xp++; }while(--n);
	return sum;
}
float fir1_2(n,cp,xp) int n; float*cp,*xp;
{	float s0=0,s1=0,s2=0,s3=0;
	n>>=2;
	do{	
		s0+=*cp++ * *xp++; 
		s1+=*cp++ * *xp++; 
		s2+=*cp++ * *xp++; 
		s3+=*cp++ * *xp++; 
	}while(--n);
	return s0+s1+s2+s3;
}
fir4_1(n,cp,xp,op) int n; float*cp,*xp,*op;
{	float s0=0,s1=0,s2=0,s3=0, c0,c1,c2,c3, x0,x1,x2,x3;
	n>>2;
		x0=*xp++;x1=*xp++;x2=*xp++;x3=*xp++;
	do{
		c0=*cp++;c1=*cp++;c2=*cp++;c3=*cp++;
		s0+=c0*x0;x0=*xp++; s1+=c0*x1;s2+=c0*x2; s3+=c0*x3;
		s0+=c1*x1;x1=*xp++; s1+=c1*x2;s2+=c1*x3; s3+=c1*x0;
		s0+=c2*x2;x2=*xp++; s1+=c2*x3;s2+=c2*x0; s3+=c2*x1;
		s0+=c3*x3;x3=*xp++; s1+=c3*x0;s2+=c3*x1; s3+=c3*x2;
	}while(--n);
	/* rest */
	op[0]=s0; op[1]=s1; op[2]=s2; op[3]=s3;
}
fir4_2(n,cp,xp,op) int n; float*cp,*xp,*op;
{	float s0=0,s1=0,s2=0,s3=0, c0,c1,c2,c3, x0,x1,x2,x3;
	n>>2;
		x0=*xp++; x1=*xp++; x2=*xp++; x3=*xp++;
		c0=*cp++; c1=*cp++; /* inserted */
	do{
		/* deleted */	     c2=*cp++; c3=*cp++;
		s0+=c0*x0; x0=*xp++; s1+=c0*x1; s2+=c0*x2; s3+=c0*x3; c0=*cp++;
		s0+=c1*x1; x1=*xp++; s1+=c1*x2; s2+=c1*x3; s3+=c1*x0; c1=*cp++;
		s0+=c2*x2; x2=*xp++; s1+=c2*x3; s2+=c2*x0; s3+=c2*x1; c2=*cp++;
		s0+=c3*x3; x3=*xp++; s1+=c3*x0; s2+=c3*x1; s3+=c3*x2; c3=*cp++;
	}while(--n);
	/* rest */
	op[0]=s0; op[1]=s1; op[2]=s2; op[3]=s3;
}

