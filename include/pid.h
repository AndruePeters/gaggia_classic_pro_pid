#ifndef PID_H
#define PID_H
/// PIDController Algorithm
///
/// \tparam RealNumber is some numerical type for this class to use such as float, integer, or some custom class
template <class RealNumber>
class PIDController {
    /// This is the target value for the algorithm
    RealNumber setPoint = 0;

    /// Gain for the proportional part of the equation, Kp
    RealNumber processVarCoefficient = 0;

    /// Gain for the integral part of the equation, Ki
    RealNumber integralCoefficient = 0;

    /// Gain for the derivative part of the equation, Kd
    RealNumber derivativeCoefficient = 0;

    /// These values are used for internal calculations for derivative and integral
    RealNumber prevError = 0;
    RealNumber integral = 0;

public:

    ///
    /// \param setPoint target value for PID
    /// \param Kp process variable gain
    /// \param Ki integral gain
    /// \param Kd derivative gain
    PIDController(RealNumber setPoint, RealNumber Kp = 0, RealNumber Ki = 0, RealNumber Kd = 0):
    setPoint(setPoint), processVarCoefficient(Kp), integral(Ki), derivativeCoefficient(Kd) {

    }

    ///
    /// \param setPoint Set the target value for PID
    void setSetPoint(RealNumber setPoint) {
        this->setPoint = setPoint;
    }

    ///
    /// \param processVarCoef set the process variable gain
    void setProcessVariableCoefficient(RealNumber processVarCoef) {
        processVarCoefficient = processVarCoef;
    }

    ///
    /// \param integralCoef set the integral gain
    void setIntegralCoefficient(RealNumber integralCoef) {
        integralCoefficient = integralCoef;
    }

    ///
    /// \param derivativeCoef set the derivative gain
    void setDerivativeCoefficient(RealNumber derivativeCoef) {
        derivativeCoefficient = derivativeCoef;
    }

    ///
    /// \param processVar Current state of the system:
    ///                   if this is a thermostat, then processVar would be the current temperature
    ///                   if this is a motor, then it might be the angular position
    /// \return value from running PID algorithm
    ///         Nothing special is done to the output, so it is the responsibility of the user to
    ///         correctly clamp/map/transform the values as needed
    RealNumber getOutput(RealNumber processVar) {
        RealNumber error = processVar - setPoint;
        integral = integral + error;
        const RealNumber derivative = error - prevError;
        const RealNumber controlVar = (processVarCoefficient * error) + (integralCoefficient * integral) + (derivativeCoefficient * derivative);

        prevError = error;
        return controlVar;
    }
};

#endif