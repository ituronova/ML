package antcolony;
import java.awt.Color;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.ApplicationFrame;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.*;
import org.jfree.chart.renderer.xy.XYBarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.xy.*;

/**
 * A time series chart.
 */
public class Chart extends ApplicationFrame {

    public double minY = Double.MAX_VALUE;
    public double maxY = -Double.MAX_VALUE;
    private String chartName = "";
    
    public Chart(final String title, final String desc) {
        super(title);
        chartName = desc;
        final XYDataset dataset = createDataset();
        final JFreeChart chart = createChart(dataset);
        XYPlot xyPlot = chart.getXYPlot();
        ValueAxis domainAxis = xyPlot.getDomainAxis();
        ValueAxis rangeAxis = xyPlot.getRangeAxis();
        domainAxis.setRange(1.0, AntColony.cmax);
        rangeAxis.setRange(minY-10, maxY+10);
        XYItemRenderer renderer = xyPlot.getRenderer();
        renderer.setSeriesPaint(0, new Color(89, 50, 139));
        
        final ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(500, 270));
        chartPanel.setMouseZoomable(true, false);
        setContentPane(chartPanel);
        this.setDefaultCloseOperation(ApplicationFrame.DISPOSE_ON_CLOSE);
    }

    /**
     * Creates a sample dataset.
     * 
     * @return a sample dataset.
     */
    private XYDataset createDataset() {
      //final TimeSeries series = new TimeSeries("Radom line");         
       XYSeries series = new XYSeries("");
       for(int i = 0; i < AntColony.cmax; i++)
       {
           series.add(i+1, AntColony.shortMax[i]);
           minY = Math.min(AntColony.shortMax[i], minY);
           maxY = Math.max(AntColony.shortMax[i], maxY);
       }
       
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }
    
    /**
     * Creates a chart.
     * 
     * @param dataset  the dataset.
     * 
     * @return a chart.
     */
    private JFreeChart createChart(final XYDataset dataset){
        JFreeChart chart = ChartFactory.createXYLineChart(
            chartName, "Cycle", "Distance", dataset,
            PlotOrientation.VERTICAL,
            false, false, false);
        return chart;
    }
    
}