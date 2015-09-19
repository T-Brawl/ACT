package comparaisons;

import io.EcritureFichier;

public class ComparaisonRefs {
	
	public static double[] comparaison(double[] tab1, double[] tab2) {
		double[] res = new double[tab1.length];		
		for(int i = 0;i<tab1.length;i++) res[i] = tab1[i] / tab2[i]; 	
		return res;		
	}
	
	
	public static void main(String[] args) {
		// Les valeurs de x à tester pour tracer nos courbes
		int[] sizes = {1, 2,10,20,30,40,50,100,150,200,300,400,500,1000,1500,2000,5000,10000,25000,50000,75000,100000,250000,500000};
		FonctionsReference fr = new FonctionsReference(sizes);
		
		// Création des résultats
		double[][] results = new double[8][];
		results[0] = fr.puissance(1);
		results[1] = fr.puissance(2);
		results[2] = fr.logarithme();
		results[3] = fr.nlogn();
		results[4] = fr.exp();
		results[5] = fr.puissancen(Integer.parseInt(args[0]));
		results[6] = fr.factorielle();
		results[7] = fr.npuissancen();
		
		
		// Écriture du fichier de résultats
		EcritureFichier.output("data/comparaisons_refs.txt", results, sizes);
				
				
		double[][] comps = new double[4][];
		comps[0] = ComparaisonRefs.comparaison(results[2],results[0]);
		comps[1] = ComparaisonRefs.comparaison(results[2],fr.puissance(0.5));
		comps[2] = ComparaisonRefs.comparaison(results[2],fr.puissance(0.2));
		comps[3] = ComparaisonRefs.comparaison(results[2],fr.puissance(0.1));
		
		// Écriture du fichier de résultats
		EcritureFichier.output("data/comparaisons_nlog_vs_npuis.txt", comps, sizes);
		
		double[][] comps1 = new double[4][];
		comps1[0] = ComparaisonRefs.comparaison(results[1],fr.puissancen(2));
		comps1[1] = ComparaisonRefs.comparaison(fr.puissance(10),fr.puissancen(2));
		comps1[2] = ComparaisonRefs.comparaison(fr.puissance(20),fr.puissancen(2));
		comps1[3] = ComparaisonRefs.comparaison(fr.puissance(50),fr.puissancen(2));
		
		// Écriture du fichier de résultats
		EcritureFichier.output("data/comparaisons_npuisk_vs_2puisn.txt", comps1, sizes);
	}
	
}
