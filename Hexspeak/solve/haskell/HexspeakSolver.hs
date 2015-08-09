import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified Hexspeak (decode)

getVars :: TC.Parser (Integer)
getVars = do ciphertext <- TC.spaces >> TC.parseLong
             return (ciphertext) 

main = do 
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (ciphertext) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ Hexspeak.decode ciphertext
            hClose hOut
    hClose hIn