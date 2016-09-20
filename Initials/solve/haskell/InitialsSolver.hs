import System.Environment (getArgs)
import System.IO
import qualified TopCoder as TC
import qualified Initials (getInitials)

getVars :: TC.Parser (String)
getVars = do name <- TC.spaces >> TC.parseString
             return (name)

main = do
    args <- getArgs
    hIn <- openFile (head args) ReadMode
    contents <- hGetContents hIn
    case (TC.parse getVars "parse variables" contents) of
        Left err -> print err
        Right (name) -> do
            hOut <- openFile (head (tail args)) WriteMode
            hPutStr hOut $ show $ Initials.getInitials name
            hClose hOut
    hClose hIn
