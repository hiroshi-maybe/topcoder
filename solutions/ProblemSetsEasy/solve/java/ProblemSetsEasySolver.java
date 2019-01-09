import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class ProblemSetsEasySolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int E = (Integer) reader.next(Integer.class);
        reader.next();
        
        int EM = (Integer) reader.next(Integer.class);
        reader.next();
        
        int M = (Integer) reader.next(Integer.class);
        reader.next();
        
        int MH = (Integer) reader.next(Integer.class);
        reader.next();
        
        int H = (Integer) reader.next(Integer.class);
        reader.close();

        ProblemSetsEasy solver = new ProblemSetsEasy();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.maxSets(E, EM, M, MH, H));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
