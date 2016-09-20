import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class InitialsSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        String name = (String) reader.next(String.class);
        reader.close();

        Initials solver = new Initials();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.getInitials(name));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }
}
