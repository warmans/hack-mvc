<?hh
namespace HackMvc\Http;

class Uri {

    private array<\string, \string> $components;
    private Map $query;

    public function __construct(private \string $uri)
    {
        $this->components = \parse_url($uri);

        $query = array();
        \parse_str(isset($this->components['query']) ? $this->components['query'] : '', $query);
        $this->query = new \Map($query);
    }

    public function getPath(): \string
    {
        $matches = array();
        if (preg_match('#^([^\?]+)#', $this->uri, $matches)) {
            return $matches[1];
        }
        throw new \RuntimeException('Unable to parse URI');
    }

    public function getQuery(): Map 
    {
        return $this->query;
    }
}
