public class DataBase {

import java.sql.*;
import java.sql.PreparedStatement;
import javax.xml.stream.events.EndDocument;

	public static Connection getConnection() throws Exception{
		try {
			String driver = "com.mysql.jdbc.Driver";
			String url = "jdbc:mysql://24.196.52.166:3306/projetS4";
			String username = "sara.ifdn@hotmail.fr";
			String password = "Projets4";
			Class.forName(driver);
			Connection conn = DriverManager.getConnection(url,username,password);
			System.out.println("Connected");
			return conn;
		} catch(Exception e){System.out.println(e);} return null;
	}

	public static void createTables() throws Exception{
		try {
			//l‡ on est connectÈ ‡ notre base de donnÈes
			Connection con = getConnection();
			PreparedStatement create=con.prepareStatement("CREATE TABLE IF NOT EXISTS Player
            (alias VARCHAR2(30),
            email VARCHAR2(30),
            dateOfBirth DATE,
            nbWins NUMBER,
            nbForfeits NUMBER,
            CONSTRAINT pk_alias PRIMARY KEY (alias),
            CONSTRAINT ck_alias CHECK (alias IS NOT NULL),
            CONSTRAINT ck_email CHECK (email IS NOT NULL),
            CONSTRAINT ck_dob CHECK (dateOfBirth IS NOT NULL),
            CONSTRAINT ck_nbW CHECK (nbWins >= 0),
            CONSTRAINT ck_nbF CHECK (nbForfeits >= 0);");
			create.executeUpdate();

            create = con.prepareStatement("CREATE TABLE IF NOT EXISTS Game
            (idGame NUMBER,
            nameGame VARCHAR2(30),
            startDate DATE,
            startMove NUMBER,
            blackPlayer VARCHAR2(30),
            whitePlayer VARCHAR2(30),
            CONSTRAINT pk_game PRIMARY KEY (idGame),
            CONSTRAINT fk_game_bp FOREIGN KEY (blackPlayer) REFERENCES Player (alias),
            CONSTRAINT fk_game_wp FOREIGN KEY (whitePlayer) REFERENCES Player (alias),
            CONSTRAINT ck_startMv CHECK (startMove >= 0),
            CONSTRAINT ck_startDt CHECK (startDate IS NOT NULL);");
			create.executeUpdate();
            con.close();

		}catch (Exception e){
            System.out.println(e);
        }finally {
            System.out.println("function complete");
        }
	}

	public static void addPlayer(String alias, Date dateOfBirth, String email) throws Exception {
		try {
			Connection con = getConnection();
			PreparedStatement pst = con.prepareStatement(
            "BEGIN
                IF NOT EXISTS (SELECT * FROM Player WHERE alias = " + alias + "
                BEGIN
                    INSERT INTO Player VALUES (" + alias + "," +
                    dateOfBirth.toStringDate() + "," + email ", 0, 0)
                END
            END");
		    pst.executeUpdate();
            con.close();
		}catch(Exception e) {
            System.out.println(e);
        }finally {
			System.out.println("Insert Completed");
		}
	}

    public static void addGame(int id, String nameGame, Date startDate, int startMove, String bp, String wp) throws Exception {
        try {
            Connection con = getConnection();
			PreparedStatement pst = con.prepareStatement(
            "INSERT INTO Game VALUES (" + id + "," + nameGame + "," + startDate + "," + startMove + "," + bp + "," + wp + ")");
            pst.executeUpdate();
            con.close();
        }catch (Exception e) {
            System.out.println(e);
        }finally {
            System.out.println("New game added");
        }
    }

    public static void updatePlayerStats(Player bp, Player wp, char event) throws Exception {
        try {
            Connection con = getConnection();
            if (event == 'w' ) {
                PreparedStatement pst = con.prepareStatement(
                "UPDATE Player SET nbWins = nbWins + 1 WHERE alias = ?");
                if (bp.isWinner()) {
                    pst.setString(1, bp.getAlias());
                }else {
                    pst.setString(1, wp.getAlias());
                }
            }else {
                PreparedStatement pst = con.prepareStatement(
                "UPDATE Player SET nbForfeits = nbForfeits + 1 WHERE alias = ?");
                if (bp.isQuitter()) {
                    pst.setString(1, bp.getAlias());
                }else {
                    pst.setString(1, wp.getAlias());
                }
            }
            pst.executeUpdate();
            con.close();
        }catch (Exception e) {
            System.out.println(e);
        }finally {
            System.out.println("Player info updated");
        }
    }
}
