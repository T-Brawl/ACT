package travellingSalemansProblem;


import java.util.Random;
import java.util.Scanner;

import classesPb.*;

//Certificat = liste de villes (question 1)
public class CertificatTSP implements Certificat{
	
	public int[] villes;

	public CertificatTSP(TSP tsp) {
		villes = new int[tsp.nbVilles];
		this.reset();
	}

	public void saisie() {
		Scanner sc = new Scanner(System.in);
		while(isInvalid()){
			System.out.println("Certificat invalide. Ne saisissez une ville qu'une fois !");
			for (int i=0; i<villes.length; i++) {
				System.out.println("Veuillez saisir une ville :");
				villes[i]= Integer.parseInt(sc.nextLine());
			}
		}
		
	}

	public void display() {
		for(int s: villes)
			System.out.print(s+" ");
		System.out.println();
	}
	
	public int get(int ind) {
		return villes[ind];
	}

	public void alea() {
		Random dice = new Random();
		
		for (int i=0; i<villes.length; i++) {
		    int randomPosition = dice.nextInt(villes.length);
		    int tmp = villes[i];
		    villes[i] = villes[randomPosition];
		    villes[randomPosition] = tmp;
		}
	}

	public void reset() {
		for(int i=0; i< villes.length; i++){
			villes[i] = i;
		}
	}

	public boolean estDernier() {
		for(int i=0; villes.length>i;i++){
			if(villes[i]!=(villes.length-(i+1))){
				return false;
			}
		}
		return true;
	}

	public void suivant() {
		
	    // Find longest non-increasing suffix
	    int i = villes.length - 1;
	    while (i > 0 && villes[i - 1] >= villes[i])
	        i--;
	    // Now i is the head index of the suffix
	    
	    // Are we at the last permutation already?
	    if (i <= 0)
	        return;
	    
	    // Let array[i - 1] be the pivot
	    // Find rightmost element that exceeds the pivot
	    int j = villes.length - 1;
	    while (villes[j] <= villes[i - 1])
	        j--;
	    // Now the value array[j] will become the new pivot
	    // Assertion: j >= i
	    
	    // Swap the pivot with j
	    int tmp = villes[i - 1];
	    villes[i - 1] = villes[j];
	    villes[j] = tmp;
	    
	    // Reverse the suffix
	    j = villes.length - 1;
	    while (i < j) {
	        tmp = villes[i];
	        villes[i] = villes[j];
	        villes[j] = tmp;
	        i++;
	        j--;
	    }
		
	}
	
	private boolean isInvalid(){
		boolean[] tmp= new boolean[villes.length];
		int i;
		for(i=0; villes.length>i;i++){
			tmp[i]=false;
		}
		for(i=0; villes.length>i;i++){
			if(tmp[villes[i]]){
				return true;
			}
			tmp[villes[i]]=true;
		}
		return false;
	}
	
	public static void main(String[] arg) {
		System.out.println("Affichage de tous les certificats pour 5 villes");
		CertificatTSP tsp = new CertificatTSP(new TSP(5,null,0));
		int cpt=0;
		while(!tsp.estDernier())  {tsp.display(); cpt++; tsp.suivant();}
		tsp.display();
		cpt++;
		System.out.println(cpt+" certificats possibles");
	}
	
}
