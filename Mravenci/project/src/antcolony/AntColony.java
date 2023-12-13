/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package antcolony;

/**
 *
 * @author tmobilek
 */
public class AntColony {

    /**
     * @param args the command line arguments
     */
    
    /**
     * Public variables
     */
    public static int t = 0;    // time
    public static int n = -1;    // number of cities
    public static int m = -1;    // number of ants
    public static int algorithm = 0;    // algorithm choice
    public static double a = 0.0;    // initial konstant
    public static int cmax = 0; // maximal number of cycles
    public static int tn = 1;   // time increment
    public static int alpha = -1;// constant alpha
    public static int beta = -1; // constant beta
    public static double ro = -1.0;   // evaporation factor   
    public static int k = 0;    // number of iteration
    public static int c = 0;    // number of cycle
    public static double[] shortMax = new double[100]; // lenghth of shortest path
    public static int[][] shortPath = new int[100][100];   // shortest path  
    public static double Q = 0.1;   // pheromon constant
    public static int[][] cities = new int[100][2]; // city position
    public static int[][] tabu = new int[100][100];   // table of paths
    public static double[] length = new double[100];// lenght of paths
    public static double[][][] f = new double[100][100][101]; // intenzity of pheromone
    public static double[][] df = new double[100][100]; // increment of pheromone intenzity
    public static double[][] elit = new double[100][100]; // increment in case of elitist strategy
    public static double q0 = 0.75; // probability in case of ant colony system
    
    public static void main(String[] args) {
        MainFrame mainWindow = new MainFrame();
    }
    
    public static void AntColony()
    {
        double shortest = Double.POSITIVE_INFINITY;
        
        int shortID = 0;
        if(c == 0)
            shortMax[c] = Double.POSITIVE_INFINITY;
        else
        {
            shortMax[c] = shortMax[c-1];
            for(int i = 0; i < n; i++)
            {
                shortPath[c][i] = shortPath[c-1][i];
                length[i] = 0;
            }
        }
        for(int i = 0; i < n; i++)
        {
            length[i] = 0;
        }
        
        // initialization
        double[][] d = init();  // init matrix d         
        for(int i =0; i< n; i++) // initialize pheromone field
        {
            for(int j =0; j< n; j++)
            {
                if(c == 0) // first cycle
                {
                    f[i][j][t] = a;
                    df[i][j] = 0.0;
                }
                elit[i][j] = 0; 
            }
        }
            
            k = 0;
            for(int i = 0; i < m; i++) // place ants
            {
                tabu[i][k] = 0;//(int)(Math.random()*n);
            }
            k++; // increse iteration
            for(;k < n; k++)
            {
                for(int i = 0; i < m; i++) // place ants
                {
                    tabu[i][k] = probability(i, d, f, tabu); 
                    length[i] += d[tabu[i][k-1]][tabu[i][k]];
                }
            }
            for(int i = 0; i < m; i++) 
            { // add length between last and first city
                length[i] += d[tabu[i][n-1]][tabu[i][0]];
            }
            // find shortest 
            for (int i = 0; i < m; i++)
            {
                //System.out.print("Lenght in shortest" + length[i] + "\n");
                if (length[i] < shortest)
                {
                    shortest = length[i];
                    shortID = i;
                }
            } 
            if(shortest < shortMax[c]) // actualize shortest path
            {
                for(int i = 0; i < n; i++)
                {
                    shortPath[c][i] = tabu[shortID][i];
                    shortMax[c] = shortest;
                }
            }
            if(algorithm == 1) // ant-density algorithm
            {
                //System.out.print("Ant-density");
                for(k = 0;k < n-1; k++) //actualize pheromone field increment
                {
                    for(int i = 0; i < m; i++)
                    {
                        if(k == 0)
                            df[tabu[i][k]][tabu[i][k+1]] = Q;
                        else df[tabu[i][k]][tabu[i][k+1]] += Q;
                    }
                }
                for(int i = 0; i < m; i++)
                {
                   df[tabu[i][n-1]][tabu[i][0]] += Q;
                }   
            }
            else if(algorithm == 2) // ant-quantity algorithm 
            {
                //System.out.print("Ant-quantity");
                for(k = 0;k < n-1; k++) //actualize pheromone field increment
                {
                    for(int i = 0; i < m; i++)
                    {
                        if(k == 0)
                            df[tabu[i][k]][tabu[i][k+1]] = Q/d[tabu[i][k]][tabu[i][k+1]];
                        else df[tabu[i][k]][tabu[i][k+1]] += Q/d[tabu[i][k]][tabu[i][k+1]];
                    }
                }
                for(int i = 0; i < m; i++)
                {
                   df[tabu[i][n-1]][tabu[i][0]] += Q/d[tabu[i][n-1]][tabu[i][0]];
                }   
            }
            else
            {
               // System.out.print("Classical or elite\n");
                for(k = 0;k < n-1; k++) //actualize pheromone field increment
                {
                    for(int i = 0; i < m; i++)
                    {
                        if(k == 0)
                        {
                            df[tabu[i][k]][tabu[i][k+1]] = Q/length[i];
                            //System.out.print(Q/length[i] + "\n");
                        }
                        else
                        {
                            df[tabu[i][k]][tabu[i][k+1]] += Q/length[i];
                            //System.out.print(Q/length[i] + "\n");
                        }
                        if(algorithm == 3)
                        { 
                            for(int r = 0; r < n-1; r++)
                            {
                                if(shortPath[c][r] == tabu[i][k] && shortPath[c][r+1] == tabu[i][k+1])
                                    elit[tabu[i][k]][tabu[i][k+1]] += 1;
                            }
                            if(shortPath[c][n-1] == tabu[i][k] && shortPath[c][0] == tabu[i][k+1])
                                elit[tabu[i][k]][tabu[i][k+1]] += 1;
                        }
                    }
                }
                for(int i = 0; i < m; i++)
                {
                    df[tabu[i][n-1]][tabu[i][0]] += Q/length[i];
                    if(algorithm == 3)
                    { 
                        //System.out.print("Elite");
                        for(int r = 0; r < n-1; r++)
                        {
                            if(shortPath[c][r] == tabu[i][n-1] && shortPath[c][r+1] == tabu[i][0])
                                elit[tabu[i][n-1]][tabu[i][0]] += 1;
                        }
                        if(shortPath[c][n-1] == tabu[i][n-1] && shortPath[c][0] == tabu[i][0])
                            elit[tabu[i][n-1]][tabu[i][0]] += 1;
                    }
                }   
            }
            if(algorithm == 3)
            {
                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        df[i][j] += elit[i][j]*Q/shortMax[c];
                    }
                }
            }
            for(int i = 0; i< n; i++) // actualize pheromone field
            {
                for(int j =0; j< n; j++)
                {
                    f[i][j][t+tn] = (1-ro)*f[i][j][t]+df[i][j];                        
                }
            }
            t += tn;    // increase time
            for(int i = 0; i < m; i++)
            {
               length[i] = 0;
            }
           /* for(int i = 0; i < m; i++){
            for(int j = 0; j < k; j++)
            {
                System.out.print(tabu[i][j] + " ");
            }
            System.out.print("\n");
            }
            System.out.print("\n");
            */
           /* for(int i = 0; i < n; i++)  // compute distance matrix
            {
                for(int j = 0; j < n; j++)
                    {
                        System.out.print(elit[i][j] + " ");

                    }
                System.out.print('\n');
            }*/
    } 
    
    
    public static int probability(int ant, double[][] d, double [][][] f, int [][] tabu){
        double maxP = 0; // maximum probability
        double p = 0; // probability
        int city = 0;   // city with maximum probability
        double sum = 0;
        double q = Math.random(); // random number for ant colony system
        int act = tabu[ant][k-1]; // actual ant position
        boolean skip = false;                
        for(int j = 0; j<n; j++)
        {
            skip = false;
            for(int path = 0; path < k; path++)
            {
                if(j == tabu[ant][path])
                    skip = true;
            }
            if(skip != true)
               sum += (Math.pow(f[act][j][t], alpha) * Math.pow(1/d[act][j], beta));
        }
        
        for(int j = 0; j<n; j++)
        {
            skip = false;
            for(int path = 0; path < k; path++)
            {
                if(j == tabu[ant][path])
                    skip = true;
            }
            if(!skip)
            {
                p = Math.pow(f[act][j][t], alpha) * Math.pow(1/d[act][j], beta)/ sum; 
                if(algorithm == 4 && q <= q0) // variant Ant Colony System
                {
                    if(Math.pow(f[act][j][t], alpha) * Math.pow(1/d[act][j], beta) > maxP)
                    {
                        city = j;
                        maxP = f[act][j][t] * Math.pow(1/d[act][j], beta);
                    }
                }
                else
                {
                    if(p > maxP)
                        city = j;
                    if(p ==  maxP && Math.random() > 0.5)
                    {
                        city = j;
                        maxP = p;
                    }
                }
            }              
        }
    return city;
    }
    
    public static double[][] init(){
        // initialize values according to setting
        Q = 0.8;
        a = 1.1;
        
        double [][]d = new double [n][n];
        
        for(int i = 0; i < n; i++)  // compute distance matrix
        {
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    double dx = (double)(Math.abs(cities[i][0] - cities[j][0]));
                    double dy = (double)(Math.abs(cities[i][1] - cities[j][1]));
                    
                    d[i][j] = Math.sqrt((dx*dx) + (dy*dy));
                }
            }
        }
        return d;
    }
}
