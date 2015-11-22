package travellingSalemansProblem;

import classesPb.NP;
import classesPb.NPRed;

public class HamiltonPathRed extends NPRed {

	public int nbSommets;
	public boolean[][] aretes;

	public HamiltonPathRed(int nb, boolean graphe[][]){
		nbSommets=nb;
		aretes=graphe;
	}
	
	public NP red() {
		int sommets = nbSommets+1;
		boolean [][] graphe = new boolean[sommets][sommets];
		
		for(int i = 0; i <= nbSommets; i++) 
			for(int j = 0; j <= nbSommets; j++) 
				graphe[i][j] = (i == nbSommets || j == nbSommets ) ? true : aretes[i][j];
		
		return new HamiltonCycleRed(sommets, graphe);
	}
}
