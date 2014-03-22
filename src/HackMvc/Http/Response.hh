<?hh
namespace HackMvc\Http;

class Response {

	public function __construct(private Status $status, private \Map $headers, private \string $body)
	{}

	public function flush()
	{
		//todo
	}
}
