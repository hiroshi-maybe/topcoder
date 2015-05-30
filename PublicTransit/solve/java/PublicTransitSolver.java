import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class PublicTransitSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int R = (Integer) reader.next(Integer.class);
        reader.next();
        
        int C = (Integer) reader.next(Integer.class);
        reader.close();

        PublicTransit solver = new PublicTransit();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.minimumLongestDistance(R, C));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
