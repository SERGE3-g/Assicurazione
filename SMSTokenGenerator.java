import javax.xml.bind.DatatypeConverter;//import javax.xml.bind.DatatypeConverter;
import java.security.SecureRandom;

public class SMSTokenGenerator {

    // Generate a random token
    public static String generateToken() {
        SecureRandom random = new SecureRandom()//;
        byte[] tokenBytes = new byte[4];
        random.nextBytes(tokenBytes);

        String token = DatatypeConverter.printHexBinary(tokenBytes);
        return token;
    }

    public static void main(String[] args) {
        String token = generateToken();
        System.out.println(token);
    }

}
