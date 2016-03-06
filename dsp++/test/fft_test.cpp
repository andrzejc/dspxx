/*!
 * @file fft_test.cpp
 * 
 * @author Andrzej Ciarkowski <mailto:andrzej.ciarkowski@gmail.com>
 */

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp> 

#include <dsp++/float.h>
#include <dsp++/const.h>

#include <stdexcept>
#include <dsp++/fftw/dft.h>
#include <dsp++/fft.h>
#include <vector>
#include <functional>
#include <algorithm>

typedef std::vector<std::complex<float>, dsp::dft::fftw::allocator<std::complex<float> > > fcvec;
typedef std::vector<float, dsp::dft::fftw::allocator<float> > fvec;
typedef dsp::dft::fft<std::complex<float>, std::complex<float> > fftf;

const float fin[] = {0.0519835390150547027587891,0.0983107760548591613769531,-1.43392241001129150390625,0.468489587306976318359375,0.3444426059722900390625,0.490921586751937866210938,-0.413305729627609252929688,0.0346787385642528533935547,-0.0848314315080642700195312,0.62817156314849853515625,0.127602145075798034667969,-0.7727935314178466796875,1.431363582611083984375,-1.2295396327972412109375,-1.38972628116607666015625,-1.17881858348846435546875,-1.4060056209564208984375,-1.097560882568359375,0.0806045085191726684570312,1.8615539073944091796875,-0.34088838100433349609375,1.669760227203369140625,-0.29529631137847900390625,0.151921659708023071289062,2.01970577239990234375,0.338179677724838256835938,1.4398021697998046875,-0.388313859701156616210938,-1.472661495208740234375,-0.584733664989471435546875,0.596652984619140625,-2.15467071533203125,0.100025385618209838867188,-0.425098240375518798828125,0.000424166093580424785614014,-0.90946805477142333984375,-0.844160020351409912109375,0.205709442496299743652344,1.11414015293121337890625,0.191271215677261352539062,0.89698314666748046875,0.917069911956787109375,-0.87563097476959228515625,-0.72571408748626708984375,0.8929107189178466796875,-0.397684007883071899414062,0.00486457487568259239196777,-0.959506511688232421875,-1.734462261199951171875,1.1477367877960205078125,-0.175794988870620727539062,-1.48741471767425537109375,-0.903969705104827880859375,0.75055217742919921875,-0.0347129963338375091552734,0.454735279083251953125,-1.0018589496612548828125,-0.906838834285736083984375,-0.91524469852447509765625,0.983295023441314697265625,2.195284366607666015625,0.485093533992767333984375,-0.6695702075958251953125,-0.225742131471633911132812,0.253088027238845825195312,-0.414076268672943115234375,-2.2193605899810791015625,0.142802193760871887207031,-1.3418014049530029296875,1.38122951984405517578125,0.356077492237091064453125,0.964861392974853515625,-1.0345160961151123046875,-1.16839230060577392578125,0.348437696695327758789062,-1.015879154205322265625,0.9454171657562255859375,0.110665537416934967041016,-0.8965227603912353515625,0.013499108143150806427002,0.66532266139984130859375,-0.586069524288177490234375,-0.663049280643463134765625,1.94110929965972900390625,-0.282924979925155639648438,-0.489227771759033203125,0.778746068477630615234375,-0.991149485111236572265625,-0.957114756107330322265625,1.75152790546417236328125,0.3698732852935791015625,-0.994955003261566162109375,1.27542245388031005859375,0.8425314426422119140625,-1.99918472766876220703125,-0.638518273830413818359375,-0.624772131443023681640625,1.48423445224761962890625,1.59912478923797607421875,1.04370415210723876953125,0.0354072228074073791503906,0.342545598745346069335938,-0.0726161524653434753417969,-2.7476279735565185546875,-0.753986835479736328125,1.232922077178955078125,-2.498858928680419921875,1.41528403759002685546875,0.000374746305169537663459778,0.283460825681686401367188,0.387970745563507080078125,-0.00377467391081154346466064,1.0898435115814208984375,-0.344244986772537231445312,-0.532878458499908447265625,-1.61131227016448974609375,0.262129127979278564453125,1.4945774078369140625,-0.1275198459625244140625,-1.48781192302703857421875,-0.160379678010940551757812,1.47996008396148681640625,-0.497648924589157104492188,0.0136702433228492736816406,-1.318931102752685546875,0.0383985042572021484375,-0.36704528331756591796875,-0.273127287626266479492188,0.118014983832836151123047,-0.78582274913787841796875,0.26088225841522216796875,0.00989283062517642974853516,-1.0550615787506103515625,-0.82806313037872314453125,-1.08970081806182861328125,0.325428158044815063476562,-1.65573108196258544921875,0.67952382564544677734375,-1.5794589519500732421875,-0.896226346492767333984375,0.564834535121917724609375,0.441808253526687622070312,1.86370241641998291015625,-0.200015261769294738769531,-0.701186835765838623046875,0.960499227046966552734375,-2.105144977569580078125,0.204875573515892028808594,0.902800858020782470703125,-0.895418226718902587890625,0.92526376247406005859375,0.746282875537872314453125,-0.256231844425201416015625,-0.179044157266616821289062,0.736645221710205078125,0.957998752593994140625,0.250259101390838623046875,1.19547307491302490234375,0.745553195476531982421875,0.720254600048065185546875,-1.27558887004852294921875,0.16838836669921875,1.15603351593017578125,-1.37322294712066650390625,0.431607097387313842773438,-0.2302496433258056640625,-0.557229936122894287109375,1.99923610687255859375,1.1392323970794677734375,1.25498068332672119140625,0.931541979312896728515625,-0.82950627803802490234375,-0.587544262409210205078125,0.75171363353729248046875,-0.218231663107872009277344,-1.909742832183837890625,-0.294979721307754516601562,-0.98931157588958740234375,-2.2981040477752685546875,0.60292541980743408203125,0.7019345760345458984375,0.464262783527374267578125,0.0260195359587669372558594,1.083919048309326171875,0.644237041473388671875,-1.94543588161468505859375,1.04012644290924072265625,-1.50448811054229736328125,1.00695049762725830078125,-0.185456305742263793945312,-0.50279390811920166015625,-0.480185329914093017578125,0.974519789218902587890625,0.7611463069915771484375,0.501329720020294189453125,-0.191234901547431945800781,-1.02636015415191650390625,-0.3948705196380615234375,-0.195910587906837463378906,0.83296239376068115234375,-0.6595199108123779296875,-1.38498783111572265625,1.6007688045501708984375,0.481887131929397583007812,-0.8790910243988037109375,1.2561798095703125,1.59590244293212890625,1.388375759124755859375,0.501272261142730712890625,1.55631077289581298828125,-1.17219257354736328125,1.843996524810791015625,1.02105629444122314453125,-0.206906273961067199707031,1.89772832393646240234375,-1.0355322360992431640625,1.45216619968414306640625,0.339065730571746826171875,0.864633977413177490234375,0.0702400282025337219238281,-0.211273401975631713867188,1.06923663616180419921875,-1.5412895679473876953125,-0.481734454631805419921875,-0.666445672512054443359375,-0.0967006683349609375,-0.88742983341217041015625,0.354755491018295288085938,-1.05872058868408203125,-0.310961633920669555664062,-0.180336043238639831542969,1.2638576030731201171875,1.3571903705596923828125,1.10826432704925537109375,-0.431782692670822143554688,0.6468346118927001953125,-0.388741821050643920898438,-0.0215326976031064987182617,-0.0874161943793296813964844,1.5266811847686767578125,-0.521002292633056640625,0.668087661266326904296875,1.63782274723052978515625,0.677146017551422119140625,2.8127467632293701171875,-0.141328200697898864746094,0.920926153659820556640625,-0.0304565839469432830810547,0.40521633625030517578125,0.629320323467254638671875,-0.727176249027252197265625,0.324609279632568359375,0.333916634321212768554688,1.04137766361236572265625,-0.325356006622314453125,-2.034451961517333984375,-0.0210760105401277542114258,0.630379199981689453125,0.332539081573486328125,1.07985532283782958984375,0.697901546955108642578125,-0.0332117751240730285644531,-0.145651593804359436035156,0.0894334465265274047851562,-0.352666676044464111328125,0.520996570587158203125,-0.84587466716766357421875,-0.0951519086956977844238281,-0.0849485322833061218261719,1.84478700160980224609375,0.790941894054412841796875,-1.58352410793304443359375,1.1526043415069580078125,0.6201789379119873046875,-0.92104089260101318359375,-0.4999058246612548828125,-0.185297951102256774902344,-0.8666095733642578125,-0.596571147441864013671875,0.121147602796554565429688,-1.0854613780975341796875,0.114814691245555877685547,-1.0562627315521240234375,-0.29779183864593505859375,0.396242678165435791015625,-0.124624863266944885253906,-1.29888474941253662109375,-0.40105259418487548828125,-0.610598027706146240234375,0.8419363498687744140625,0.285728007555007934570312,-1.20487511157989501953125,2.01991939544677734375,0.539350688457489013671875,-0.8506343364715576171875,-1.592098236083984375,-0.695016086101531982421875,-1.0352528095245361328125,0.581140816211700439453125,0.89915430545806884765625,-0.07891547679901123046875,-0.638698041439056396484375,0.422191441059112548828125,0.396646708250045776367188,-0.420790404081344604492188,-1.00611913204193115234375,0.0654262602329254150390625,-1.07182562351226806640625,0.697381496429443359375,0.626608371734619140625,2.0859444141387939453125,0.949481666088104248046875,0.406155079603195190429688,-0.36944806575775146484375,0.639667510986328125,1.3363208770751953125,0.51238155364990234375,0.50877749919891357421875,-0.194369360804557800292969,1.55211532115936279296875,-0.760924279689788818359375,-0.78639984130859375,-1.78847873210906982421875,-0.33775150775909423828125,1.070838451385498046875,-0.94927465915679931640625,-2.118378162384033203125,-1.64044249057769775390625,-1.1730747222900390625,0.0792027041316032409667969,-0.705684006214141845703125,0.710921347141265869140625,-0.987967789173126220703125,0.329774707555770874023438,1.15571749210357666015625,-0.126489177346229553222656,-0.396379202604293823242188,-0.29049777984619140625,2.22977542877197265625,-1.076260089874267578125,-1.26988685131072998046875,-0.3282439708709716796875,-0.217612966895103454589844,0.304466307163238525390625,-0.63756215572357177734375,-0.675750255584716796875,-0.786223590373992919921875,2.2243974208831787109375,0.857707202434539794921875,-0.387319296598434448242188,2.9203898906707763671875,0.459517806768417358398438,-0.84974956512451171875,0.0914294198155403137207031,1.359736919403076171875,-0.411399304866790771484375,-1.96276628971099853515625,0.723827838897705078125,-0.376613616943359375,-0.57938158512115478515625,1.017729282379150390625,-1.53167998790740966796875,0.0963650271296501159667969,0.3730428218841552734375,0.92862987518310546875,0.160315021872520446777344,0.27119433879852294921875,-0.6378281116485595703125,-0.3515369892120361328125,-0.443396061658859252929688,-0.274372607469558715820312,-0.599173843860626220703125,-1.25939524173736572265625,-0.209488973021507263183594,0.213797375559806823730469,-1.41940748691558837890625,-0.0277021378278732299804688,-0.70795238018035888671875,1.9437587261199951171875,0.66075193881988525390625,0.48991811275482177734375,-0.0624178536236286163330078,0.195382088422775268554688,0.85976445674896240234375,-0.85903775691986083984375,2.4452092647552490234375,1.74247086048126220703125,0.390587329864501953125,-0.6956522464752197265625,1.03464925289154052734375,0.912684917449951171875,0.19937813282012939453125,0.19666194915771484375,0.486054450273513793945312,-1.74422395229339599609375,1.0517003536224365234375,-0.558723866939544677734375,-0.0442780293524265289306641,-1.36898791790008544921875,-0.0994589403271675109863281,-0.71665370464324951171875,-1.07519137859344482421875,0.99267184734344482421875,0.17834842205047607421875,1.29817831516265869140625,0.7434322834014892578125,0.246084660291671752929688,2.0226209163665771484375,0.8836591243743896484375,-0.0912036970257759094238281,-0.283052653074264526367188,-0.53889858722686767578125,0.495249927043914794921875,-0.228666394948959350585938,-0.0397722274065017700195312,-0.102166883647441864013672,-1.374244213104248046875,1.15007603168487548828125,-1.73235309123992919921875,0.849911510944366455078125,1.4128844738006591796875,-0.726764202117919921875,0.264403611421585083007812,-2.618000507354736328125,-1.63510036468505859375,-1.35966908931732177734375,1.55695641040802001953125,0.141924038529396057128906,-0.62679421901702880859375,-0.75568258762359619140625,-0.71304047107696533203125,0.47250080108642578125,-0.584750473499298095703125,0.689541637897491455078125,-0.799614012241363525390625,-1.653382778167724609375,1.224357128143310546875,-0.6928012371063232421875,1.22363376617431640625,-0.3869607448577880859375,-0.788545787334442138671875,0.897513687610626220703125,-0.0750811547040939331054688,1.46356070041656494140625,-0.386349111795425415039062,0.618223667144775390625,-0.89328861236572265625,-0.0572190061211585998535156,1.864572048187255859375,-0.491529911756515502929688,0.430232375860214233398438,0.960358798503875732421875,-0.478244930505752563476562,-1.4917171001434326171875,1.95050144195556640625,-0.0487393401563167572021484,1.09367477893829345703125,-0.192465692758560180664062,-0.76481735706329345703125,-0.353751480579376220703125,0.874460279941558837890625,-0.791256964206695556640625,0.41179525852203369140625,-0.376953572034835815429688,-0.330326735973358154296875,0.99876487255096435546875,-0.817412853240966796875,2.1037533283233642578125,-0.0601274184882640838623047,0.995851993560791015625,-1.1838810443878173828125,-0.602940499782562255859375,0.0997601598501205444335938,0.46484363079071044921875,0.169791132211685180664062,0.465682804584503173828125,1.38770580291748046875,-0.40673339366912841796875,-0.110449440777301788330078,0.419968932867050170898438,-0.98140609264373779296875,0.04321765899658203125,-1.4496901035308837890625,0.379643470048904418945312,0.744178235530853271484375,0.513360440731048583984375,1.1962559223175048828125,0.164304867386817932128906,-1.85561907291412353515625,0.581699848175048828125,0.394888192415237426757812,-0.81281411647796630859375,-0.390700310468673706054688,0.23245108127593994140625,0.641355693340301513671875,-0.0959349796175956726074219,0.436242640018463134765625,-0.138302341103553771972656,-0.396141350269317626953125,-1.68806934356689453125,1.9913780689239501953125,-0.681494891643524169921875,-1.43433201313018798828125,-0.685668528079986572265625,-0.6405999660491943359375,-2.1721346378326416015625,-0.0505770370364189147949219,0.6407487392425537109375,0.210774019360542297363281,-0.71236646175384521484375,0.3747556209564208984375,2.938976287841796875,-1.58977258205413818359375,-0.106171451508998870849609,-0.909269630908966064453125,0.494044452905654907226562,-1.34834563732147216796875,0.317028522491455078125,0.34807240962982177734375,-0.00897968281060457229614258,3.0420777797698974609375,0.403895914554595947265625,1.51238000392913818359375,0.198499664664268493652344,2.5790922641754150390625,-0.318128079175949096679688,2.6793506145477294921875,0.4561984539031982421875,0.102019675076007843017578,-0.495238333940505981445312,-0.731393992900848388671875,0.0292218625545501708984375,-0.0224111713469028472900391,0.50404751300811767578125,-0.376214057207107543945312,0.0425296910107135772705078,-0.754967153072357177734375,-1.264842510223388671875,0.374993711709976196289062,1.8829596042633056640625,-0.365152299404144287109375,-0.594353377819061279296875,1.6527879238128662109375,0.311750739812850952148438,0.125697553157806396484375,-0.135308325290679931640625,-0.640606224536895751953125,-1.15316450595855712890625,-0.857982099056243896484375,-0.833003342151641845703125,-1.78974044322967529296875,0.252029240131378173828125,-0.206956163048744201660156,0.95052731037139892578125,0.0340504720807075500488281,-0.305252552032470703125,-0.115045420825481414794922,0.74177300930023193359375,2.16544818878173828125,0.426089972257614135742188,-0.52207553386688232421875,0.364248573780059814453125,0.929060041904449462890625,-1.66453707218170166015625,-0.176622897386550903320312,0.391553699970245361328125,2.3274013996124267578125,-0.104184873402118682861328,1.71366012096405029296875,0.0918681398034095764160156,-0.385411083698272705078125,-0.0108497487381100654602051,1.22004878520965576171875,-0.419241696596145629882812,0.7083618640899658203125,0.856999933719635009765625,-1.2128317356109619140625,-2.3619825839996337890625,-1.28142058849334716796875,0.688478648662567138671875,2.1333789825439453125,-1.59512889385223388671875,1.5870358943939208984375,-0.15758955478668212890625,1.20882761478424072265625,1.44023191928863525390625,-1.717992305755615234375,-1.7476236820220947265625,0.358185619115829467773438,0.798908412456512451171875,2.597783565521240234375,0.822399318218231201171875,0.374572902917861938476562,-0.206175401806831359863281,0.449623376131057739257812,-0.595381677150726318359375,-0.0859704092144966125488281,0.774708211421966552734375,1.21437418460845947265625,-2.5500843524932861328125,0.59465062618255615234375,0.216644927859306335449219,-1.2277696132659912109375,-0.866610825061798095703125,1.38068974018096923828125,-0.4364612102508544921875,-2.44091033935546875,-1.0313737392425537109375,-0.70303857326507568359375,-1.00459384918212890625,-0.8991158008575439453125,-0.318546622991561889648438,0.0574690550565719604492188,1.218738079071044921875,1.13424217700958251953125,0.55823552608489990234375,1.4843728542327880859375,-1.165869235992431640625,0.157932072877883911132812,0.249890863895416259765625,-0.889984428882598876953125,0.449651271104812622070312,-1.7262136936187744140625,0.62525999546051025390625,-0.122782729566097259521484,-0.9775264263153076171875,1.77216231822967529296875,0.5582172870635986328125,-2.8010151386260986328125,0.81650292873382568359375,0.0515303350985050201416016,-1.81765830516815185546875,0.90275752544403076171875,-0.823292076587677001953125,-0.0899871066212654113769531,2.051399707794189453125,0.00744403479620814323425293,-0.718512594699859619140625,0.446070998907089233398438,0.80366790294647216796875,-0.76612758636474609375,-0.448332458734512329101562,0.100149922072887420654297,0.186814859509468078613281,0.0411143675446510314941406,-0.46078777313232421875,0.248321160674095153808594,1.27772033214569091796875,0.0171694401651620864868164,0.0399580374360084533691406,-1.13245677947998046875,-1.0127506256103515625,-2.4218599796295166015625,0.804340898990631103515625,0.273365467786788940429688,0.959589421749114990234375,-0.893348395824432373046875,0.760445892810821533203125,-0.355847269296646118164062,-0.337520122528076171875,-1.592801570892333984375,-0.566532194614410400390625,0.683292806148529052734375,0.387563645839691162109375,0.231586232781410217285156,0.159246623516082763671875,-0.221633404493331909179688,-0.240651607513427734375,0.473654776811599731445312,-0.75406682491302490234375,0.8990099430084228515625,-0.370528757572174072265625,1.036548137664794921875,-0.407069742679595947265625,-1.0113527774810791015625,-0.0597905293107032775878906,0.753360807895660400390625,0.318924844264984130859375,0.61546933650970458984375,0.7821972370147705078125,0.198016628623008728027344,-0.345615535974502563476562,-0.538987696170806884765625,0.430950582027435302734375,-0.516352832317352294921875,-1.16878974437713623046875,-0.667733013629913330078125,0.664457023143768310546875,0.204991057515144348144531,1.69911420345306396484375,-0.60503232479095458984375,0.206737965345382690429688,-1.28734338283538818359375,0.383506029844284057617188,-0.102590762078762054443359,-1.5122163295745849609375,0.9613780975341796875,0.19407093524932861328125,-0.379711598157882690429688,0.77807986736297607421875,-0.7379894256591796875,0.0851343721151351928710938,0.464268594980239868164062,-1.102725505828857421875,0.979728400707244873046875,0.63887310028076171875,0.812085688114166259765625,-0.78660929203033447265625,-0.70835649967193603515625,0.403288692235946655273438,-0.655162274837493896484375,-0.608103692531585693359375,0.390182226896286010742188,-1.2198932170867919921875,-0.253959476947784423828125,-1.10599911212921142578125,1.3664848804473876953125,-0.314751893281936645507812,-0.194645598530769348144531,-0.0273797456175088882446289,0.80881023406982421875,-1.29363524913787841796875,1.07745230197906494140625,0.79891121387481689453125,-0.396449387073516845703125,1.01347446441650390625,0.70404517650604248046875,-0.225839957594871520996094,0.584231555461883544921875,-0.00196504499763250350952148,-2.7034952640533447265625,-0.812623083591461181640625,0.561994016170501708984375,-0.918159902095794677734375,0.462727963924407958984375,-1.049610137939453125,0.274612963199615478515625,-0.395863145589828491210938,0.220168322324752807617188,-0.567365705966949462890625,2.1285030841827392578125,-0.00891020055860280990600586,1.1723301410675048828125,-0.572691500186920166015625,-0.5348856449127197265625,-0.517373979091644287109375,-0.747474849224090576171875,-0.729293644428253173828125,0.0519539155066013336181641,-0.319065898656845092773438,-1.59721982479095458984375,-0.30240237712860107421875,-0.338627874851226806640625,-0.645132482051849365234375,1.9321019649505615234375,1.3648917675018310546875,0.66296660900115966796875,1.130207061767578125,0.124289788305759429931641,-0.682977855205535888671875,-0.330551654100418090820312,-0.874837338924407958984375,-1.61127948760986328125,1.9929811954498291015625,0.67502915859222412109375,-0.0411258041858673095703125,0.54319703578948974609375,-0.16144430637359619140625,0.475778549909591674804688,-1.027292728424072265625,0.242342486977577209472656,-0.7691981792449951171875,-0.85003817081451416015625,-0.376206219196319580078125,0.911843001842498779296875,0.709688007831573486328125,-1.25843775272369384765625,-0.490723043680191040039062,2.6628048419952392578125,1.0413143634796142578125,-0.238854244351387023925781,-0.426219195127487182617188,-0.0154165457934141159057617,-0.0451898686587810516357422,-0.705159366130828857421875,-0.0359417721629142761230469,2.69673442840576171875,0.95148408412933349609375,0.9166948795318603515625,-1.48292648792266845703125,1.1724321842193603515625,2.1092331409454345703125,1.1927196979522705078125,-0.361030250787734985351562,0.485987722873687744140625,-1.2639005184173583984375,-0.72189617156982421875,-0.86512792110443115234375,1.40160882472991943359375,0.562043368816375732421875,-0.283090144395828247070312,0.561218678951263427734375,-2.0417897701263427734375,0.948870837688446044921875,1.71542298793792724609375,1.81778049468994140625,0.080534875392913818359375,-1.25408685207366943359375,-0.154917314648628234863281,-1.97373676300048828125,-0.649407565593719482421875,0.398751318454742431640625,0.92525923252105712890625,-0.6941394805908203125,-0.635655105113983154296875,1.701057910919189453125,0.626721084117889404296875,0.00339291337877511978149414,0.743563234806060791015625,-0.765115559101104736328125,0.265217721462249755859375,0.7229688167572021484375,0.277557462453842163085938,-0.472627073526382446289062,0.724147021770477294921875,0.45654773712158203125,1.67119538784027099609375,0.547078311443328857421875,0.376218289136886596679688,0.419011145830154418945312,-1.7954337596893310546875,-0.860427796840667724609375,-0.753439426422119140625,0.64607346057891845703125,-0.378301888704299926757812,1.49063789844512939453125,-0.488404929637908935546875,0.104250900447368621826172,0.499690681695938110351562,2.4234268665313720703125,0.198605105280876159667969,-0.244388267397880554199219,-1.049503803253173828125,-0.935452401638031005859375,1.998041629791259765625,-0.647752463817596435546875,0.339501410722732543945312,-0.3617174625396728515625,-1.519773960113525390625,-0.324550330638885498046875,0.179436847567558288574219,0.246584862470626831054688,-1.08241879940032958984375,0.698219358921051025390625,1.49680435657501220703125,-1.21235764026641845703125,0.418997794389724731445312,-0.700957596302032470703125,2.5349462032318115234375,-1.86044514179229736328125,0.330117672681808471679688,-0.71672880649566650390625,-0.9396822452545166015625,0.112770073115825653076172,-0.223858416080474853515625,0.554912865161895751953125,-0.689959049224853515625,-0.72838866710662841796875,0.09484016895294189453125,-0.596654117107391357421875,-0.115737505257129669189453,-0.712011992931365966796875,-0.272707730531692504882812,1.25291538238525390625,0.127606242895126342773438,-0.711893737316131591796875,0.824081718921661376953125,-0.07878339290618896484375,0.936111509799957275390625,-1.43246471881866455078125,1.63483715057373046875,0.461684733629226684570312,-0.0475227758288383483886719,-0.5801665782928466796875,-1.6712052822113037109375,1.00277245044708251953125,0.509774029254913330078125,0.90476143360137939453125,-0.549016296863555908203125,-0.903209686279296875,1.6937129497528076171875,-1.2608797550201416015625,1.02614009380340576171875,0.209235459566116333007812,-0.513391792774200439453125,2.30023288726806640625,-2.069538593292236328125,-0.804360330104827880859375,-0.61548554897308349609375,-0.5831940174102783203125,-0.810069143772125244140625,-0.0569236949086189270019531,0.408800989389419555664062,0.90578734874725341796875,-0.879000723361968994140625,1.24323618412017822265625,-1.7766802310943603515625,-0.5604593753814697265625,1.47255611419677734375,-0.59111309051513671875,1.08959114551544189453125,-0.355161398649215698242188,0.4897000789642333984375,0.7228183746337890625,-0.812104880809783935546875,0.217409417033195495605469,-1.5326135158538818359375,-0.906591892242431640625,-0.176589339971542358398438,-0.0719206184148788452148438,-0.0254414901137351989746094,-0.442719250917434692382812,-0.763177692890167236328125,0.64226353168487548828125,1.5975551605224609375,-0.6203315258026123046875,-0.686018645763397216796875,0.547386467456817626953125,-0.4617311954498291015625,0.198553055524826049804688,-1.2532827854156494140625,0.629943192005157470703125,0.7315037250518798828125,0.409614533185958862304688,0.0871774405241012573242188,0.0200172550976276397705078,-0.466802626848220825195312,-0.949900925159454345703125,-0.317423254251480102539062,0.5858027935028076171875,0.0375133641064167022705078,1.03810322284698486328125,-0.135187178850173950195312,-0.0119396168738603591918945,-0.59028112888336181640625,-0.0979252159595489501953125,-0.5530736446380615234375,-0.322926938533782958984375,0.301013439893722534179688,-0.533519744873046875,-0.674196064472198486328125,0.805442750453948974609375,-1.46278095245361328125,-0.954712092876434326171875,-1.21316254138946533203125,-0.253958970308303833007812,-0.293876916170120239257812,-0.343765825033187866210938,-1.24845778942108154296875,0.148692056536674499511719,-0.275208562612533569335938,-0.258315056562423706054688,0.234748780727386474609375,1.37230098247528076171875,-0.445996791124343872070312,1.08106911182403564453125,2.073940753936767578125,-1.28632843494415283203125,-1.30119335651397705078125,1.1503007411956787109375,0.95803034305572509765625,0.680487096309661865234375,0.668949425220489501953125,-0.428171455860137939453125,0.225304380059242248535156,-0.512419760227203369140625,-1.19121897220611572265625,-0.286578655242919921875,0.4334304332733154296875,0.543933689594268798828125,-0.0277220830321311950683594,-1.6267259120941162109375,-0.90985310077667236328125,0.526708900928497314453125,0.19334125518798828125,-0.49822127819061279296875,-0.176819577813148498535156,1.60449612140655517578125,0.0310612171888351440429688,-1.02903568744659423828125,-1.21856021881103515625,-1.16346204280853271484375,-0.69561803340911865234375,-1.09210026264190673828125,1.7370007038116455078125,0.727173328399658203125,0.107458449900150299072266,-0.24290263652801513671875,-0.8829362392425537109375,1.85901463031768798828125,-0.160267755389213562011719,-0.54700863361358642578125,-0.634297847747802734375,-0.310263931751251220703125,1.66168439388275146484375,1.0476562976837158203125,-0.216911107301712036132812,0.526469647884368896484375,1.02884197235107421875,-0.6731755733489990234375,-1.79217433929443359375,0.838463306427001953125,-1.71555531024932861328125,0.0544752106070518493652344,-1.1194946765899658203125,0.970285594463348388671875,0.0866380631923675537109375,0.495437443256378173828125,2.01727581024169921875,0.5788104534149169921875,0.65519106388092041015625,0.106228493154048919677734,-1.09012115001678466796875,-0.0387823171913623809814453};

BOOST_AUTO_TEST_SUITE(fft)

BOOST_AUTO_TEST_CASE(test_fft_64)
{
	BOOST_CHECK_NO_THROW(fftf(64, NULL, NULL));
}

BOOST_AUTO_TEST_CASE(test_fft_65)
{
	BOOST_CHECK_THROW(fftf(65, NULL, NULL), std::domain_error);
}

BOOST_AUTO_TEST_CASE(test_fft_536870912)
{
	BOOST_CHECK_THROW(fftf(536870912, NULL, NULL), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_fft_equals_fftw)
{
	std::complex<float> in1[64] = {0}, in2[64] = {0};
	std::complex<float> out1[64], out2[64];

	dsp::dft::fft<std::complex<float>, std::complex<float> > fft(64, in1, out1, dsp::dft::sign::forward);
	dsp::dft::fftw::dft<std::complex<float>, std::complex<float> > dft(64, in2, out2, dsp::dft::sign::forward);

	for (size_t i = 0; i < 64; ++i)
		in1[i] = in2[i] = static_cast<float>(sin(20 * DSP_M_PI * i / 64));

	fft();
	dft();

	BOOST_CHECK(std::equal(out2, out2 + 64, out1,
			dsp::within_range<std::complex<float> >(std::numeric_limits<float>::epsilon() * 100)));
}

BOOST_AUTO_TEST_CASE(test_fft_r2c)
{
	const size_t N = 1024;
	fvec in(N);
	fcvec out(N);
	dsp::dft::fftw::dft<float, std::complex<float> > fftw(N, &in[0], &out[0]);
	std::copy(fin, fin + N, in.begin());
	fftw();

	fcvec ref = out;

	dsp::dft::fft<float, std::complex<float> > fft(N, &in[0], &out[0]);
	fft();

	BOOST_CHECK(std::equal(ref.begin(), ref.begin() + N / 2 + 1, out.begin(),
			dsp::within_range<std::complex<float> >(std::numeric_limits<float>::epsilon() * 1000)));
}

BOOST_AUTO_TEST_CASE(test_fft_two_way)
{
	const size_t N = 256;
	fvec in(N), res(N);
	fcvec out(N);

	dsp::dft::fft<float, std::complex<float> > fft(N, &in[0], &out[0]);
	std::copy(fin, fin + N, in.begin());

	fft();

 	dsp::dft::fft<std::complex<float>, float> ifft(N, &out[0], &res[0]);
	ifft();

	std::transform(res.begin(), res.end(), res.begin(), std::bind2nd(std::divides<float>(), (float)N));

	BOOST_CHECK(std::equal(in.begin(), in.end(), res.begin(),
			dsp::within_range<std::complex<float> >(std::numeric_limits<float>::epsilon() * 10)));
}

BOOST_AUTO_TEST_SUITE_END()
