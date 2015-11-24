package travellingSalemansProblem;
import classesPb.*;

public class TSP extends NP{
	public int nbVilles;
	public int[][] distances;
	public int longueurTournee;

	public TSP(int nb, int dist[][], int lg){
		this.nbVilles=nb;
		this.distances=dist;
		this.longueurTournee=lg;
	}

	public CertificatTSP cert() { 
		return new CertificatTSP(this);
	}

	public boolean estCorrect(Certificat c){ 
		int res=0;
		for(int i = 0;i < nbVilles;i++){
			res += distances[c.get(i)][c.get((i+1)%nbVilles)];
			if(res > longueurTournee) return false;
		}
		return res <= longueurTournee;
	}
}
