import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class LastDigitSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        long S = (Long) reader.next(Long.class);
        reader.close();

        LastDigit solver = new LastDigit();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.findX(S));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
