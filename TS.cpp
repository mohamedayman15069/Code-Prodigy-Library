int fun(int x)
{
    return 1;
}

double TS(double s, double e){
  for(double sz = e - s; sz > 1e-18; sz*=2.0 / 3){
    double a = s + sz / 3;
    double b = a + sz / 3;
    if(fun(a) > fun(b))
      s += sz / 3;
  }
  return s;
}

// normal : maximize
int TS(){
    int lo = 0, hi = 1e9;
    while(lo+3 < hi){
            int p1 = lo + (hi-lo)/3;
            int p2 = hi - (hi-lo)/3;
            if(fun(p1) < fun(p2)) lo = p1;
            else hi = p2;
        }
        int ans = 0; 
    for(int i = lo; i <= hi; i++)
		ans = max(ans, int(fun(i)+ 1e-8));
    
    return ans; 
}

//add this
