package travellingSalemansProblem;

import classesPb.NP;
import classesPb.NPRed;

public class HamiltonCycleRed extends NPRed {

	public int nbSommets;
	public boolean[][] aretes;

	public HamiltonCycleRed(int nb, boolean graphe[][]){
		nbSommets=nb;
		aretes=graphe;
	}
	
	public NP red() {
		int nbVilles = nbSommets;
		int longueurTournee = nbVilles;
		int[][] dist = new int[nbVilles][nbVilles];
		
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				dist[i][j] = aretes[i][j] ? 1 : 0b11111111111111111111111111111111;
			}
		}
		
		return new TSP(nbVilles, dist, longueurTournee);
	}

}
