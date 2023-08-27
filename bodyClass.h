using namespace std;

class bodyClass {
    public:
        // constructor (default)
        bodyClass() {
            x = 0;
            y = 0;
            x_dot = 0;
            y_dot  = 0;
            m = 0;
        }


        //constructor (user-defined)
        bodyClass(const double input_x,const double input_y,const double input_x_dot,const double input_y_dot,const double input_m) {
            x = input_x;
            y= input_y;
            x_dot = input_x_dot;
            y_dot  =input_y_dot;
            m = input_m;
        };


        //destructor
        ~bodyClass() {
        }


        //get functions
        double getX() {return x;}
        double getY() {return y;}
        double getX_dot() {return x_dot;}
        double getY_dot() {return y_dot;}
        double getM() {return m;}


        //set functions
        void setX(const double input_x) { x=input_x;}
        void setY(const double input_y) {y=input_y;}
        void setX_dot(const double input_x_dot) {x_dot = input_x_dot;}
        void setY_dot(const double input_y_dot) {y_dot= input_y_dot;}
        void setM(const double input_m) {m=input_m;}


        //overall set function
        void setVals(const double input_x,const double input_y,const double input_x_dot,const double input_y_dot,const double input_m) {
            x=input_x;
            y=input_y;
            x_dot=input_x_dot;
            y_dot= input_y_dot;
            m=input_m;
        }

        //Operator overloading methods
        //METHOD: multiplies everything except m by scalar
        bodyClass multiplyBody(const double& scalar) {
            return(bodyClass(scalar*x, scalar*y, scalar*x_dot, scalar*y_dot, m));
        }

        bodyClass divideBody(const double& divisor) {
            return(bodyClass(x/divisor, y/divisor, x_dot/divisor, y_dot/divisor, m));
        }

        //METHOD: adds existing body to input body. This doesnt make sense physcially but needs to happen during the calculation of k1,k2, etc
        bodyClass addBody(bodyClass& addedBody) {
            bodyClass newBody(x+addedBody.getX(), y+addedBody.getY(), x_dot+addedBody.getX_dot(), y_dot+addedBody.getY_dot(), m);
            return newBody;
        }

        //METHOD: exists for the final summation at the end of runge kutta
        bodyClass finalSum(bodyClass& k1_body, bodyClass& k2_3_body, bodyClass& k4_body) {

            double xSum = x+k1_body.getX()+k2_3_body.getX()+k4_body.getX();
            double ySum = y+k1_body.getY()+k2_3_body.getY()+k4_body.getY();
            double x_dotSum = x_dot+k1_body.getX_dot()+k2_3_body.getX_dot()+k4_body.getX_dot();
            double y_dotSum = y_dot+k1_body.getY_dot()+k2_3_body.getY_dot()+k4_body.getY_dot();
            return bodyClass(xSum, ySum, x_dotSum, y_dotSum, m);
        }


    private:
        double x;
        double y;
        double x_dot;
        double y_dot;
        double m;
};