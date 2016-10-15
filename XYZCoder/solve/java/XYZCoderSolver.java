import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class XYZCoderSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        int room = (Integer) reader.next(Integer.class);
        reader.next();
        
        int size = (Integer) reader.next(Integer.class);
        reader.close();

        XYZCoder solver = new XYZCoder();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.countWays(room, size));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
