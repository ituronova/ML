/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package antcolony;

import java.awt.Point;

/**
 *
 * @author tmobilek
 */
public class Path {

    private City start;
    private City end;
    
    public Path(City start, City end){
        this.start = start;
        this.end = end;
    }
    
    public City findStart(){
        return start;
    }
    
    public City findEnd(){
        return end;
    }

    public Point locStart(){
        return start.locCity();
    }
    
    public Point locEnd(){
        return end.locCity();
    }
}
