<?hh
namespace Catfacts;

class FactsDb 
{
    public function __construct(private \SQLite3 $sqlite)
    {}

    public function getFact(\int $id): \mixed
    {
        return $this->fetchOne('SELECT * FROM fact WHERE id=:id', array(':id'=>$id));
    }

    public function getFacts(): \mixed
    {
        return $this->fetchAll('SELECT * FROM fact');
    }

    public function getRandomFact(): \mixed
    {
        return $this->fetchOne('SELECT * FROM fact ORDER BY RANDOM() LIMIT 1');
    }

    public function addFact(\string $fact): \bool
    {
        $stmt = $this->getStmt('INSERT INTO fact (`fact`) VALUES (:fact)', array(':fact'=>$fact));
         if ($stmt->execute() ) {
            return true;
         }
         return false;
    }

    public function editFact(\int $id, \string $fact): \mixed
    {
        $stmt = $this->getStmt('REPLACE INTO fact (`id`, `fact`) VALUES (:id, :fact)', array(':id'=> $id, ':fact'=>$fact));
        return $stmt->execute();
    }

    public function deleteFact(\int $id) 
    {
        $stmt = $this->getStmt('DELETE FROM fact WHERE id=:id', array(':id'=> $id));   
        return $stmt->execute();
    }

    private function fetchOne(\string $query, array $params=array()): \mixed
    {
        $result = $this->getStmt($query, $params)->execute();
        return $result->fetchArray(SQLITE3_ASSOC);
    }

    private function fetchAll(\string $query, array $params=array()): \mixed
    {
        $result = $this->getStmt($query, $params)->execute();
        $rows = array();
        while($row = $result->fetchArray(SQLITE3_ASSOC)){
            $rows[] = $row;
        }
        return $rows;
    }

    private function getStmt(\string $query, array $params=array()): \SQLite3Stmt
    {
        $stmt = $this->sqlite->prepare($query);
        foreach ($params as $placeholder => $value) {
            $stmt->bindValue($placeholder, $value);    
        }
        return $stmt;
    }
}