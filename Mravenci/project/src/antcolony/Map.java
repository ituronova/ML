/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package antcolony;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.util.ArrayList;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import java.awt.Image;
import java.awt.Graphics;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Path2D;
import java.awt.geom.Rectangle2D;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author tmobilek
 */
public class Map extends JPanel {
    private City city1 = null;
    private City city2 = null;
    public static ArrayList<City> cities;
    private static ArrayList<Path> pathes;
    public static int citiesCount = 0;
        
    public Map(){
        super();
        setMouseListenerAction();
        this.city1 = null;
        this.city2 = null;
        this.cities = new ArrayList<>();
        this.pathes = new ArrayList<>();
    }
    
    private void setMouseListenerAction(){
        this.addMouseListener(new MouseAdapter(){
            @Override
            public void mousePressed(MouseEvent evt){
                if(SwingUtilities.isLeftMouseButton(evt))
                {
                    createCity(evt);    // create city
                }
            }
        });   
    }
    
    public void paintArrowHead(Graphics2D graph, Point p1, Point p2){
         graph.setPaint(Color.blue.brighter());
         graph.setStroke(new BasicStroke(3));
         double angle = Math.atan2(p2.y - p1.y, p2.x - p1.x);
         double anchor = Math.toRadians(30);
         double i = angle + anchor;
         for(int j = 0; j < 2; j++)
         {
            //graph.draw(new Line2D.Double(p2.x, p2.y, p2.x - 15 * Math.cos(i), p2.y - 15 * Math.sin(i)));
            i = angle - anchor;
         }
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D graph = (Graphics2D) g;
        try {
            Image bgImage = ImageIO.read(new File("C:\\Data\\VUT\\SFC Soft Computing\\Projekt\\cr.jpg"));
            super.paintComponent(graph);
            graph.drawImage(bgImage, 0, 0, getWidth(), getHeight(), this);
        } catch (IOException ex) {
            Logger.getLogger(Map.class.getName()).log(Level.SEVERE, null, ex);
        }
        graph.setStroke(new BasicStroke(3));
        for(Path edge : pathes)
        {
            Line2D.Double pPath = new Line2D.Double(edge.locStart().x, edge.locStart().y,edge.locEnd().x, edge.locEnd().y);
            graph.setColor(new Color(213, 206, 215));
            graph.setStroke(new BasicStroke(2));
            graph.draw(pPath);
        }
        for(Path path : pathes)
        {
            Line2D.Double pPath = new Line2D.Double(path.locStart().x, path.locStart().y, path.locEnd().x, path.locEnd().y);
            Point l1 = path.findStart().location;
            Point l2 = path.findEnd().location;
            for(int i = 0; i < AntColony.n-1; i++)
            {
                Point p1 = cities.get(AntColony.shortPath[AntColony.c][i]).location;
                Point p2 = cities.get(AntColony.shortPath[AntColony.c][i+1]).location;
                if((l1 == p2 && l2 == p1)||(l1 == p1 && l2 == p2)) 
                {                       
                    graph.setColor(new Color(142, 50, 168)); 
                    graph.setStroke(new BasicStroke(3));
                    graph.draw(pPath);
                    paintArrowHead(graph, p1, p2);
                }
            }
            if(AntColony.n > 0)
            {
                Point p1 = cities.get(AntColony.shortPath[AntColony.c][AntColony.n-1]).location;
                Point p2 = cities.get(AntColony.shortPath[AntColony.c][0]).location;
                if((l1 == p2 && l2 == p1)||(l1 == p1 && l2 == p2))  
                {
                    graph.setColor(new Color(142, 50, 168)); 
                    graph.setStroke(new BasicStroke(3));
                    graph.draw(pPath);
                    paintArrowHead(graph, p1, p2);
                }
            }
        }
        for (City citie : cities)
        {
            Rectangle2D pCity = new Rectangle2D.Double(citie.locCity().x-1,citie.locCity().y-1, 4, 4);
            Rectangle2D block = new Rectangle2D.Double(citie.locCity().x+7,citie.locCity().y-23, 22, 17);
            graph.setColor(new Color(89, 50, 139));
            graph.draw(block);
            graph.fill(block);
            for(int i = 0; i < AntColony.n; i++)
            {
                if(AntColony.shortPath[AntColony.c][0] == cities.indexOf(citie))
                {
                    graph.setStroke(new BasicStroke(2));
                    graph.setColor(new Color(255, 125, 252));  
                    graph.fill(pCity);
                }
            }
            graph.setStroke(new BasicStroke(3));
            graph.draw(pCity);
            graph.setStroke(new BasicStroke(4));
            graph.setColor(Color.white);
            graph.setFont(new Font("default", Font.BOLD, 17));
            graph.drawString(Integer.toString(cities.indexOf(citie)), citie.locCity().x+10, citie.locCity().y-10);
        }
    }
    
    private void createCity(MouseEvent evt){
        City cityNew = new City(evt.getPoint());
        this.cities.add(cityNew); // add new city
        citiesCount++;
        for (City citie : cities) 
        { // create pathes with all cities
            this.city1 = citie;
            this.city2 = cityNew; 
            this.pathes.add(new Path(this.city1, this.city2));
        }
        repaint();
    }
    
    public void hightLight(int c)
    {
       repaint();
       AntColony.c = c;
    } 
}
