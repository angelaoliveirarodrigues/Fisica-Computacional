void Frequencia(vector<vector<int>>& M, int WhiteValue, int nrows, int ncols){
 vector<int> ColourFreq(WhiteValue +1);
  vector<float> FreqRela(WhiteValue+1);
    for(int i =0 ; i<nrows ; i++){
      for(int j=0; j<ncols ; j++){
        ColourFreq[M[i][j]]++;
        };
      };
    for(int i =0 ; i<WhiteValue+1; i++){
      FreqRela[i]=ColourFreq[i]/(ncols*nrows) *100;
      printf("A cor %d tem : %d elementos", i ,ColourFreq[i]);
      printf("A cor %d tem : %d frequência", i ,FreqRela[i]);
      };
    }