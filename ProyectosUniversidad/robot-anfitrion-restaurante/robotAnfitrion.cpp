#include <ros/ros.h>
#include <uv_msgs/ImageBoundingBox.h>
#include <uv_msgs/ImageBoundingBoxListStamped.h>
#include <sound_play/SoundRequest.h> 
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <time.h>
#include <vector>
#include <string.h>

using namespace std;


ros::Publisher demoSound_pub;
sound_play::SoundRequest sayMsg;

const float recepcion[3] = {10.2, 14.0, 2.2}; //position.x,position.y,orientation.z
const float mesa1[3] = {8.5, 15.0, 0.0};
const float mesa2[3] = {5.0, 15.5, 0.0};
const float mesa3[3] = {3.3, 14.2, 0.2};
const float mesa4[3] = {3.2, 15.5, 0.0};

const float coordenadasMesas[5][3] = {{10.2, 14.0, 2.2}, //position.x,position.y,orientation.z
								      {8.5, 15.0, 0.0},
									  {5.0, 15.5, 0.0},
									  {3.3, 14.2, 0.2},
									  {3.2, 15.5, 0.0}};
									  
float coordPosx;
float coordPosy;
float coordOrz;

bool galerasOcupadas=false;

int num_personas;

//Matriz de ocupación de las mesas.
vector<vector<int> > ocupacionMesas(4, vector<int>(5));

//Banderas para cambiar de estado.
bool Estado1 = true;
bool Estado2 = false;
bool Estado3 = false;

bool rostroDetectado = false;

void pausa(double seconds){

	clock_t goal = seconds*CLOCKS_PER_SEC + clock();
	while (goal > clock());
}


void imprimirEstados(){

	for(int i=0; i<=ocupacionMesas.size()-1; i++){
	
		cout << "Mesa " << i+1 << " = " << ocupacionMesas[i][0] << endl;
	}
}

void face_tracker(const uv_msgs::ImageBoundingBoxListStamped::ConstPtr& facesbBox){

	if(!rostroDetectado){
		cout << "Rostro detectado." << endl;
		rostroDetectado = true;
	}
}


//Función para detectar cuando el robot llegó a su destino.
int status_id = 0;
void navStatusCallBack(const actionlib_msgs::GoalStatusArray::ConstPtr &status){

    status_id = 0;

    if (!status->status_list.empty()){
    	actionlib_msgs::GoalStatus goalStatus = status->status_list[0];
    	status_id = goalStatus.status;
    }
    if(status_id==0){
    	ROS_INFO("0");
    }
    if(status_id==2 and cont%100==0){
    	ROS_INFO("En camino.");
    }
    if(status_id==3 and cont%100==0){
    	ROS_INFO("Destino alcanzado.");
    }
}


void decirFrase(string frase){

	sayMsg.sound=-3;
	sayMsg.command=1;
	sayMsg.arg2 = "voice_kal_diphone";
	sayMsg.arg = frase;
	demoSound_pub.publish(sayMsg);
}


geometry_msgs::PoseStamped newPosition;

clock_t tiempoPausaQ;
double tiempoPausa = 4.0;
double tiempoActual;


//Estado 1. Detectar clientes en la recepción.
void estado1(){

	if(rostroDetectado and Estado1){
	
		imprimirEstados();
		decirFrase("Hello my name is UVerto, can I help you?");
		pausa(3);
		decirFrase("How many people are you?");
		
		cin >> num_personas;
		
		decirFrase("Follow me please");
		pausa(2);
		
		//Codigo para determinar mesa;
		
		if(num_personas<4){
		
			for(int i=0; i<=ocupacionMesas.size()-1; i++){
			
				if(!ocupacionMesas[i][0]){
				
					ocupacionMesas[i][0]=1;
					coordPosx = coordenadasMesas[i+1][0];
					coordPosy = coordenadasMesas[i+1][1];
					coordOrz = coordenadasMesas[i+1][2];
					break;
				}
			}
		}
		
		else if(num_personas==4){
		
			if(!galerasOcupadas){
			
			for(int i=2; i<=ocupacionMesas.size()-1; i++){
			
				if(!ocupacionMesas[i][0]){
				
					ocupacionMesas[i][0]=1;
					coordPosx = coordenadasMesas[i+1][0];
					coordPosy = coordenadasMesas[i+1][1];
					coordOrz = coordenadasMesas[i+1][2];
					
					if(ocupacionMesas[3][0]){
						
						galerasOcupadas=true;
					}
					
					break;
				}
			}
			
			}
			
			else if(galerasOcupadas and ocupacionMesas[1][0]){
			
				decirFrase("I am sorry, we do not have available tables");
				pausa(3);
				rostroDetectado = false;
			}
			
			else if(galerasOcupadas and !ocupacionMesas[1][0]){
			
				for(int i=0; i<=1; i++){
					
					if(!ocupacionMesas[i][0]){
						
						ocupacionMesas[i][0]=1;
						coordPosx = coordenadasMesas[i+1][0];
						coordPosy = coordenadasMesas[i+1][1];
						coordOrz = coordenadasMesas[i+1][2];
						break;
					}
				}
			}
		}
		
		else{
		
			decirFrase("Our tables have a maximum capacity of four persons, i am sorry, i can not attend you");
			pausa(10.0);
			rostroDetectado = false;
		}
		
		//Actualización de estados.
		
		if(rostroDetectado){
		
			Estado1=false;
			Estado2=true;
			tiempoPausaQ = tiempoPausa*CLOCKS_PER_SEC + clock();
		}
	}
}


//Estado 2. Llevar a los clientes a su mesa.
bool fase2 = false;
void estado2(double x, double y, double z){
	
	if(Estado2){
	
		newPosition.pose.position.x=x;
		newPosition.pose.position.y=y;
		newPosition.pose.orientation.z=z;
		newPosition.pose.orientation.w=0.5;
		
		if(status_id==2 and clock()>tiempoPausaQ){
			fase2 = true;
		}
		if(status_id==3 and fase2){
			fase2 = false;
			Estado2 = false;
			Estado3 = true;
			cout << "Ya llegue." << endl;
			decirFrase("This is your table, enjoy your dinner");
			pausa(3.0);
			decirFrase("See you");
			pausa(1.0);
			tiempoPausaQ = tiempoPausa*CLOCKS_PER_SEC + clock();
			imprimirEstados();
		}
	}
}


//Estado 3. Volver a la recepción.
void estado3(double x, double y, double z){

	if(Estado3){
		
		newPosition.pose.position.x=x;
		newPosition.pose.position.y=y;
		newPosition.pose.orientation.z=z;
		newPosition.pose.orientation.w=0.5;
		
		if(status_id==2 and clock()>tiempoPausaQ){
			fase2 = true;
		}
		
		if(status_id==3 and fase2){
			fase2 = false;
			Estado3 = false;
			rostroDetectado = false;
			Estado1 = true;
			cout << "Ya llegue." << endl;
			tiempoPausaQ = tiempoPausa*CLOCKS_PER_SEC + clock();
		}
	}
}





int main(int argc, char** argv){




ros::init(argc, argv, "robotAnfitrion");
ros::NodeHandle n;

ros::Publisher sendMapPosition;
ros::Subscriber move_base_status_sub;
ros::Subscriber faceDetect = n.subscribe("/faceDetection/validFaces",1,face_tracker);

demoSound_pub = n.advertise<sound_play::SoundRequest>("/robotsound", 1);
sendMapPosition = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal",10);
move_base_status_sub = n.subscribe<actionlib_msgs::GoalStatusArray>("/move_base/status", 10, &navStatusCallBack); // *

tiempoPausaQ = tiempoPausa*CLOCKS_PER_SEC + clock();

while (ros::ok()){
  
    newPosition.header.stamp==ros::Time::now();
	newPosition.header.frame_id="map";
	
	estado1();
	estado2(coordPosx, coordPosy, coordOrz);
	estado3(recepcion[0], recepcion[1], recepcion[2]);
	sendMapPosition.publish(newPosition);

	cont++;
	ros::spinOnce();
}
  
    return 0;
}
