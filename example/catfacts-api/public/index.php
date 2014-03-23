<?hh
//class loading
require_once(__DIR__.'/../../../src/ClassLoader.hh');
$class_loader = new HackMvc\ClassLoader();
$class_loader->addNamespace('HackMvc', __DIR__ . '/../../../src/');
$class_loader->addNamespace('Catfacts', __DIR__ . '/../src');
$class_loader->register();

//configure services
$sl = new \HackMvc\Service\Locator();

$sl->registerFactory('db', function($sl) {
    return new \SQLite3(__DIR__.'/../db/catfacts.sqlite');
});

$sl->registerFactory('factsdb', function($sl) {
    return new \Catfacts\FactsDb($sl->getService('db'));
});

//create application
$app = new \HackMvc\Application($sl);

//get all facts
$app->get('#/api/v1/fact(/)?$#', function($route, $sl) use ($app) { 
    return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>$sl->getService('factsdb')->getFacts()));
});

//get specific fact
$app->get('#/api/v1/fact/(?<id>[0-9]+)$#', function($route, $sl) use ($app) { 
    $id = (int)$route->getMatchedSubstrings()['id'];

    if ($fact = $sl->getService('factsdb')->getFact($id)) {
        return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>$fact));
    } else {
        return $app->json(array('success'=>false, 'msg'=>'Fact was not found', 'payload'=>null), 404);
    }
});

//get random fact
$app->get('#/api/v1/fact/random$#', function($route, $sl) use ($app) { 
    if ($fact = $sl->getService('factsdb')->getRandomFact()) {
        return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>$fact['fact']));
    } else {
        return $app->json(array('success'=>false, 'msg'=>'Fact was not found', 'payload'=>null), 404);
    }
});

//add a new fact
$app->post('#/api/v1/fact(/)?$#', function($route, $sl) use ($app) { 
    if ($fact = json_decode($route->getRequest()->getRawBody(), true)) {
        
        if (empty($fact['fact'])) {
            return $app->json(array('success'=>false, 'msg'=>'new fact was blank or missing fact attribute', 'payload'=>''));            
        }

        if ($sl->getService('factsdb')->addFact($fact['fact'])) {
            return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>''));    
        } else {
            return $app->json(array('success'=>false, 'msg'=>'failed to add fact for an unknown reason', 'payload'=>''));                
        }
    }
    return $app->json(array('success'=>false, 'msg'=>json_last_error_msg(), 'payload'=>''));    
});

//edit a fact
$app->put('#/api/v1/fact/(?<id>[0-9]+)$#', function($route, $sl) use ($app) { 
    if ($fact = json_decode($route->getRequest()->getRawBody(), true)) {
        
        if (empty($fact['fact'])) {
            return $app->json(array('success'=>false, 'msg'=>'new fact was blank or missing fact attribute', 'payload'=>''));            
        }
        
        $id = (int)$route->getMatchedSubstrings()['id'];
        if ($sl->getService('factsdb')->editFact($id, $fact['fact'])) {
            return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>''));    
        } else {
            return $app->json(array('success'=>false, 'msg'=>'failed to add fact for an unknown reason', 'payload'=>''));                
        }
    }
    return $app->json(array('success'=>false, 'msg'=>json_last_error_msg(), 'payload'=>''));    
});

//delete a fact
$app->delete('#/api/v1/fact/(?<id>[0-9]+)$#', function($route, $sl) use ($app) { 
    $id = (int)$route->getMatchedSubstrings()['id'];
    if ($fact = $sl->getService('factsdb')->deleteFact($id)) {
        return $app->json(array('success'=>true, 'msg'=>'', 'payload'=>''));
    } else {
        return $app->json(array('success'=>false, 'msg'=>'Fact was not deleted', 'payload'=>null));
    }
});

//create and handle request
$globals = new HackMvc\Php\Globals();
$app->handle($globals->getHttpRequest())->flush();
