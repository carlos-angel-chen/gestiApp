import { motion } from 'framer-motion';

const StatCard = ({name, icon: Icon, value, color, onClick}) => {
    return (
        <motion.div
            className='bg-gray-800 bg-opacity-50 backdrop-blur-md overflow-hidden shadow-lg rounded-xl border border-gray-700'
            whileHover={{ y: -5, boxShadow:"0 25px 50px -12px rgba(0,0,0,0.5" }}
            onClick={onClick}
        >
            <div className='px-4 py-5 sm:p-6'>
                <span className='flex itemx-center text-sm font-medium text-gray-400'>
                    <Icon size={20} className="mr-2" style={{ color }} />
                    {name}
                </span>
                <p className='mt-2 text-3x1 font-semibold text-gray-100'> {value} </p>
            </div>
        </motion.div>
    );
}

export default StatCard;