import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class UpDownHikingSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int N = (Integer) reader.next(Integer.class);
        reader.next();
        
        int A = (Integer) reader.next(Integer.class);
        reader.next();
        
        int B = (Integer) reader.next(Integer.class);
        reader.close();

        UpDownHiking solver = new UpDownHiking();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.maxHeight(N, A, B));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
