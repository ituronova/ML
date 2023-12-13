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
public class City {
    Point location;
    
    public City(Point location){
        this.location = location;
    }    
    
    public Point locCity(){
        return this.location;
    }
}
