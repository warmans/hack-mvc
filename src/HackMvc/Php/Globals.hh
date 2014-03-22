<?hh
namespace HackMvc\Php;

use HackMvc\Http;

/**
 * Take all the weird global PHP stuff and hide it here.
 */
class Globals {

	public function getHttpRequest(): Http\Request
	{
		$request = new Http\Request(
		    $_SERVER['REQUEST_METHOD'],
			new Http\Uri($_SERVER['REQUEST_URI']), 
			new \Map(apache_request_headers()) //why the fuck is this called apache_request_headers?
		);

		$request->setRawBody(file_get_contents("php://input"));

		return $request;
	}
}
