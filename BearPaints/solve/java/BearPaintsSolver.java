import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class BearPaintsSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int W = (Integer) reader.next(Integer.class);
        reader.next();
        
        int H = (Integer) reader.next(Integer.class);
        reader.next();
        
        long M = (Long) reader.next(Long.class);
        reader.close();

        BearPaints solver = new BearPaints();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.maxArea(W, H, M));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
