import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class TriangleMakingSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int a = (Integer) reader.next(Integer.class);
        reader.next();
        
        int b = (Integer) reader.next(Integer.class);
        reader.next();
        
        int c = (Integer) reader.next(Integer.class);
        reader.close();

        TriangleMaking solver = new TriangleMaking();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.maxPerimeter(a, b, c));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
